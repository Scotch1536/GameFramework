#include <Windows.h>

#include "../DebugTools/imgui/myimgui.h"
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/CDirectInput.h"
#include "../Managers/CInputManager.h"

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

	sts = CDirectXGraphics::GetInstance()->Init(
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
	CDirectXGraphics::GetInstance()->TurnOnAlphaBlending();

	//DIRECTINPUT初期化
	CDirectInput::GetInstance().Init
	(
		mApp.GetHInst() ,
		mApp.GetHWnd() ,
		CApplication::CLIENT_WIDTH ,
		CApplication::CLIENT_HEIGHT
	);

	imguiInit();

	if(mLevel != nullptr)
	{
		mLevel->Init();
	}
}

void CGame::Input()
{
	CInputManager::GetInstance().CheckInput();
}

void CGame::Update()
{
	mLevel->Update();
	mLevel->Tick();
}

void CGame::Render()
{
	mLevel->Render();
}

void CGame::LoadLevel(CLevel& level)
{
	mLevel.reset(&level);

	mLevel->Init();
}