#include <Windows.h>

#include "CGame.h"
#include "Application.h"
#include "CDirectInput.h"
#include "CDirectXGraphics.h"
#include "DX11Settransform.h"


CGame::CGame()
{}

CGame& CGame::GetInstance()
{
	static CGame instance;

	return instance;
}

long CGame::Execute(HINSTANCE hInst , int winMode)const
{
	// アプリケーション初期処理
	Application* App = Application::Instance();		// インスタンス取得
	App->Init(hInst);

	// ウインドウを表示する
	ShowWindow(App->GetHWnd() , winMode);
	UpdateWindow(App->GetHWnd());

	// メインループ
	long ret = App->MainLoop();

	// アプリケーション終了処理
	App->Dispose();

	return ret;
}

void CGame::Init()
{
	// DX11　初期化
	bool sts;

	sts = CDirectXGraphics::GetInstance()->Init(
		Application::Instance()->GetHWnd() ,
		Application::CLIENT_WIDTH ,
		Application::CLIENT_HEIGHT ,
		false);
	if(!sts)
	{
		MessageBox(Application::Instance()->GetHWnd() , "DX11 init error" , "error" , MB_OK);
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
		Application::Instance()->GetHInst() ,
		Application::Instance()->GetHWnd() ,
		Application::CLIENT_WIDTH ,
		Application::CLIENT_HEIGHT
	);
}

void CGame::Input(uint64_t deltataime)
{

}

void CGame::Update(uint64_t deltataime)
{

}

void CGame::Render(uint64_t deltataime)
{

}