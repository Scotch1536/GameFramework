#include <Windows.h>

#include "../DebugTools/imgui/myimgui.h"
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/CDirectInput.h"
#include "../Managers/CInputManager.h"
#include "../Managers/CSoundManager.h"
#include "../Actor/CDisplay2DColorActor.h"

#include "CGame.h"
#include "CApplication.h"

CGame::CGame(CGameManager& partner):mApp(*this)
{}

CGame::~CGame()
{
	imguiExit();
}

long CGame::Execute(HINSTANCE hInst , int winMode)
{
	// アプリケーション初期処理
	mApp.Init(hInst);

	// ウインドウを表示する
	ShowWindow(mApp.GetHWnd() , winMode);
	UpdateWindow(mApp.GetHWnd());

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
	sts = CreateConstantBuffer(directGraph->GetDXDevice() , sizeof(ConstantBufferViewPort) , mConstantBufferViewPort.GetAddressOf());
	if(!sts)
	{
		MessageBox(NULL , "CreateBuffer(constant buffer Light) error" , "Error" , MB_OK);
	}

	ID3D11DeviceContext* devCon = directGraph->GetImmediateContext();
	ConstantBufferViewPort cb;

	cb.ScreenWidth = CApplication::CLIENT_WIDTH;
	cb.ScreenHeight = CApplication::CLIENT_HEIGHT;

	devCon->UpdateSubresource(mConstantBufferViewPort.Get() , 0 , nullptr , &cb , 0 , 0);

	devCon->VSSetConstantBuffers(5 , 1 , mConstantBufferViewPort.GetAddressOf());
	devCon->PSSetConstantBuffers(5 , 1 , mConstantBufferViewPort.GetAddressOf());

	imguiInit();
}

void CGame::Input()
{
	CInputManager::GetInstance().CheckInput();
}

void CGame::Update()
{
	if(mLevel != nullptr)
	{
		mLevel->Tick();
		mLevel->Update();
	}
}

void CGame::Render()
{
	if(mLevel != nullptr)
	{
		mLevel->Render();
	}

	if(mLoadLevelFunction != nullptr)
	{
		mLoadLevelFunction();
		mLoadLevelFunction = nullptr;
	}
}

void CGame::LoadLevel(CLevel& level , bool isFeed , XMFLOAT3 feedColor , float oneFrameAlpha)
{
	auto loadLevel = [& , isFeed , feedColor , oneFrameAlpha]
	{
		if(isFeed&&mLevel != nullptr)
		{
			float alpha = 0.0f;
			CDisplay2DColorActor& feedScreen = *new CDisplay2DColorActor(*mLevel , XMFLOAT4(feedColor.x , feedColor.y , feedColor.z , alpha));
			feedScreen.Transform.Location.x = static_cast<float>(CApplication::CLIENT_WIDTH) / 2;
			feedScreen.Transform.Location.y = static_cast<float>(CApplication::CLIENT_HEIGHT) / 2;
			feedScreen.Transform.Scale.x = CApplication::CLIENT_WIDTH;
			feedScreen.Transform.Scale.y = CApplication::CLIENT_HEIGHT;

			while(alpha <= 1.0f)
			{
				alpha += oneFrameAlpha;

				feedScreen.SetColor(XMFLOAT4(feedColor.x , feedColor.y , feedColor.z , alpha));

				feedScreen.Update();

				mLevel->Render();
			}
			alpha = 1.0f;

			feedScreen.SetColor(XMFLOAT4(feedColor.x , feedColor.y , feedColor.z , alpha));

			feedScreen.Update();

			mLevel->Render();
		}
		mLevel.reset(&level);

		mLevel->Init();
	};

	mLoadLevelFunction = loadLevel;
}