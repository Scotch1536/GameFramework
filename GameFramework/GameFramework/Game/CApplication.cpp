//!
//!	@file
//!	@brief アプリケーションシステムのソースファイル	
//!

#include <Crtdbg.h>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <iostream>

#include "../ExternalCode/CWindow.h"
#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/CDirectxGraphics.h"
#include "../Game/CGame.h"
#include "../Managers/CGameManager.h"

#include "CApplication.h"

//スタティックメンバ初期化
const char* CApplication::WINDOW_TITLE = "Attach!";
const char*	CApplication::WINDOW_CLASS_NAME = "win32app";

const uint32_t CApplication::WINDOW_STYLE_WINDOWED = (WS_VISIBLE | WS_CAPTION | WS_SYSMENU);
const uint32_t CApplication::WINDOW_EX_STYLE_WINDOWED = (0);
const uint32_t CApplication::WINDOW_STYLE_FULL_SCREEN = (WS_VISIBLE | WS_POPUP);
const uint32_t CApplication::WINDOW_EX_STYLE_FULL_SCREEN = (0);

const uint32_t CApplication::CLIENT_WIDTH = 1280;
const uint32_t CApplication::CLIENT_HEIGHT = 720;

const float CApplication::FPS = 60;

void CApplication::Init(HINSTANCE hInstance)
{
	//メモリーリークを検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//ウインドウ作成
	CWindow* window = CWindow::Instance();
	window->RegisterClass(hInstance , WINDOW_CLASS_NAME , CS_OWNDC);

	window->SetWindow(hInstance ,
		WINDOW_STYLE_WINDOWED ,
		WINDOW_EX_STYLE_WINDOWED ,
		NULL ,
		CLIENT_WIDTH ,
		CLIENT_HEIGHT ,
		WINDOW_CLASS_NAME ,
		WINDOW_TITLE ,
		false);

	mHWnd = window->GetHandle();
	mHInstance = hInstance;
}

unsigned long CApplication::MainLoop()
{
	MSG	msg;
	ZeroMemory(&msg , sizeof(msg));

	CWindow* window = CWindow::Instance();

	uint64_t current_time = 0;
	uint64_t last_time = 0;

	CGame& game = CGameManager::GetInstance().GetGame(*this);

	//タイマ解像度をミリ秒に
	::timeBeginPeriod(1);

	while(window->ExecMessage())
	{
		//timeGetTime関数はミリ秒単位でシステム時刻を取得 
		//システム時間はWindowsを起動してからの経過時間
		current_time = ::timeGetTime();

		//デルタタイム算出
		uint64_t delta_time = current_time - last_time;

		last_time = current_time;

		//デルタタイムが更新された後で規格外の値になっていなければ
		if(delta_time != current_time && delta_time < 1000)
		{
			//ゲームマネージャーで管理しているデルタタイムを更新
			CGameManager::GetInstance().SetDeltaTime(*this , delta_time);
		}

		//ゲームフロー
		game.Input();
		game.Update();
		game.Render();

		int64_t sleep_time = 16666 - delta_time;

		if(sleep_time > 0)
		{
			float tt = sleep_time / 1000.0f;

			//指定した相対時間だけ現スレッドをブロックする (function template)
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(tt)));
		}
	}

	//タイマ解像度を元に戻す
	::timeEndPeriod(1);

	DX11SetTransform::GetInstance()->Uninit();

	//解放処理
	CDirectXGraphics::GetInstance()->Exit();

	return window->GetMessage();
}