#include <Windows.h>

#include "../ExternalTools/imgui/myimgui.h"
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/CDirectInput.h"
#include "../Managers/CInputManager.h"
#include "../Managers/CSoundManager.h"
#include "../Actor/CFeedActor.h"

#include "CGame.h"
#include "CApplication.h"

CGame::CGame(CGameManager& partner):mApp(*this)
{}

CGame::~CGame()
{
	//ImGuiの終了処理
	imguiExit();
}

long CGame::Execute(HINSTANCE hInst , int winMode)
{
	// アプリケーション初期処理
	mApp.Init(hInst);

	// ウインドウを表示する
	ShowWindow(mApp.GetHWnd() , winMode);
	UpdateWindow(mApp.GetHWnd());

	//ゲーム情報の初期化
	Init();

	// メインループ
	long ret = mApp.MainLoop();

	// アプリケーション終了処理
	mApp.Dispose();

	return ret;
}

void CGame::SetLevel(CLevel& level)
{
	mLevel.reset(&level);
}

void CGame::Init()
{
	// DX11　初期化
	bool sts;

	//サウンドマネージャー初期化
	CSoundManager::GetInstance();

	CDirectXGraphics* directGraph = CDirectXGraphics::GetInstance();

	//DirectXグラフィックスの初期化
	sts = directGraph->Init(
		mApp.GetHWnd() ,
		CApplication::CLIENT_WIDTH ,
		CApplication::CLIENT_HEIGHT ,
		false);
	if(!sts)
	{
		MessageBox(mApp.GetHWnd() , "DX11 init error" , "error" , MB_OK);
		exit(1);
	}

	//DX11SetTransformの初期化
	sts = DX11SetTransform::GetInstance()->Init();
	if(!sts)
	{
		MessageBox(NULL , "SetTransform error" , "Error" , MB_OK);
		exit(1);
	}

	//半透明設定
	directGraph->TurnOnAlphaBlending();

	//DIRECTINPUT初期化
	CDirectInput::GetInstance().Init
	(
		mApp.GetHInst() ,
		mApp.GetHWnd() ,
		CApplication::CLIENT_WIDTH ,
		CApplication::CLIENT_HEIGHT
	);

	//コンスタントバッファ作成
	sts = CreateConstantBuffer(directGraph->GetDXDevice() , sizeof(SConstantBufferViewPort) , mConstantBufferViewPort.GetAddressOf());
	if(!sts)
	{
		MessageBox(NULL , "CreateBuffer(constant buffer Light) error" , "Error" , MB_OK);
	}

	ID3D11DeviceContext* devCon = directGraph->GetImmediateContext();
	SConstantBufferViewPort cb;

	cb.ScreenWidth = CApplication::CLIENT_WIDTH;
	cb.ScreenHeight = CApplication::CLIENT_HEIGHT;

	//定数バッファの更新
	devCon->UpdateSubresource(mConstantBufferViewPort.Get() , 0 , nullptr , &cb , 0 , 0);

	//定数バッファのセット
	devCon->VSSetConstantBuffers(5 , 1 , mConstantBufferViewPort.GetAddressOf());
	devCon->PSSetConstantBuffers(5 , 1 , mConstantBufferViewPort.GetAddressOf());

	//ImGuiの初期化
	imguiInit();
}

void CGame::Input()
{
	//入力チェック処理
	CInputManager::GetInstance().CheckInput();
}

void CGame::Update()
{
	//レベルが設定されている場合
	if(mLevel != nullptr)
	{
		mLevel->Tick();			//そのレベルオリジナルで行う処理の実行
		mLevel->Update();		//全レベル共通の更新ルーティンを実行
	}
}

void CGame::Render()
{
	//レベルが設定されている場合
	if(mLevel != nullptr)
	{
		mLevel->Render();		//描画処理の実行
	}

	//ロードレベル関数が設定されているなら実行し空にする
	if(mLoadLevelFunction != nullptr)
	{
		mLoadLevelFunction();
		mLoadLevelFunction = nullptr;
	}
}

void CGame::LoadLevel(CLevel& level , bool isFeed , XMFLOAT3 feedColor , float feedTime)
{
	//フェードを行うかつレベルが設定されている場合
	if(isFeed&&mLevel != nullptr)
	{
		//ロードレベルをフェードなしで行う関数オブジェクトを作成
		auto loadLevelCall = [&]
		{
			LoadLevel(level);
		};

		//フェードアクターの作成
		new CFeedActor(*mLevel , loadLevelCall , CFeedActor::EOption::FEEDOUT , feedColor , feedTime);
	}
	else
	{
		//レベルを切り替え初期化する関数オブジェクトを作成
		auto loadLevel = [&]
		{
			mLevel.reset(&level);
			mLevel->Init();
		};

		//ロードレベル関数オブジェクトにセット
		mLoadLevelFunction = loadLevel;
	}
}