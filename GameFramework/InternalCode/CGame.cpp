#include <Windows.h>

#include "CGame.h"
#include "Application.h"
#include "DX11util.h"
#include "CDirectInput.h"

CGame::CGame()
{
}

CGame& CGame::GetInstance()
{
	static CGame instance;

	return instance;
}

long CGame::Execute(HINSTANCE hInst,int winMode)const
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
	DX11Init(
		Application::Instance()->GetHWnd() ,
		Application::CLIENT_WIDTH ,
		Application::CLIENT_HEIGHT ,
		false
	);

	//半透明設定
	TurnOnAlphablend();

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