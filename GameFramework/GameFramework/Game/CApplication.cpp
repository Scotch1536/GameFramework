//*****************************************************************************
//!	@file	Application.cpp
//!	@brief	
//!	@note	アプリケーションクラス
//!	@author	
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
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

//-----------------------------------------------------------------------------
// スタティック　メンバー
//-----------------------------------------------------------------------------
const char*			CApplication::WINDOW_TITLE = "GameFramework";
const char*			CApplication::WINDOW_CLASS_NAME = "win32app";

const uint32_t		CApplication::WINDOW_STYLE_WINDOWED = (WS_VISIBLE | WS_CAPTION | WS_SYSMENU);
const uint32_t		CApplication::WINDOW_EX_STYLE_WINDOWED = (0);
const uint32_t		CApplication::WINDOW_STYLE_FULL_SCREEN = (WS_VISIBLE | WS_POPUP);
const uint32_t		CApplication::WINDOW_EX_STYLE_FULL_SCREEN = (0);

const uint32_t		CApplication::CLIENT_WIDTH = 1280;
const uint32_t		CApplication::CLIENT_HEIGHT = 720;

uint32_t			CApplication::SYSTEM_WIDTH = 0;
uint32_t			CApplication::SYSTEM_HEIGHT = 0;

const float			CApplication::FPS = 60;

//==============================================================================
//!	@fn		CApplication
//!	@brief	コンストラクタ
//!	@param	
//!	@retval	
//==============================================================================
CApplication::CApplication(CGame& partner): m_SystemCounter(0)
{}

//==============================================================================
//!	@fn		~Application
//!	@brief	デストラクタ
//!	@param	
//!	@retval	
//==============================================================================
CApplication :: ~CApplication()
{
	Dispose();
}


//==============================================================================
//!	@fn		InitSystemWH
//!	@brief	システム領域の幅と高さを初期化
//!	@param	
//!	@retval	
//==============================================================================
void CApplication::InitSystemWH()
{

}

//==============================================================================
//!	@fn		Init
//!	@brief	初期化
//!	@param	インスタンスハンドル
//!	@retval	
//==============================================================================
bool CApplication::Init(HINSTANCE h_Instance)
{
	// メモリーリークを検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#ifdef _DEBUG
	//// コンソールを割り当てる
	//AllocConsole();

	//// 標準出力の割り当て
	//freopen_s(&m_fp , "CON" , "w" , stdout);
#endif
	// 幅と高さ初期化
	InitSystemWH();

	// ウインドウ作成
	CWindow* window = CWindow::Instance();
	window->RegisterClass(h_Instance , WINDOW_CLASS_NAME , CS_OWNDC);

	window->SetWindow(h_Instance ,
		WINDOW_STYLE_WINDOWED ,
		WINDOW_EX_STYLE_WINDOWED ,
		NULL ,
		CLIENT_WIDTH + SYSTEM_WIDTH ,
		CLIENT_HEIGHT + SYSTEM_HEIGHT ,
		WINDOW_CLASS_NAME ,
		WINDOW_TITLE ,
		false);

	// HWND
	m_hWnd = window->GetHandle();

	//
	m_hInst = h_Instance;
	return true;
}

//==============================================================================
//!	@fn		Dispose
//!	@brief  終了処理
//!	@param	
//!	@retval	
//==============================================================================
void CApplication::Dispose()
{
#ifdef _DEBUG
	//// 標準出力クローズ
	//fclose(m_fp);
	//// コンソール開放
	//::FreeConsole();
#endif
	return;
}

//==============================================================================
//!	@fn		MainLoop
//!	@brief	メインループ
//!	@param	
//!	@retval	メッセージID
//==============================================================================
unsigned long CApplication::MainLoop()
{
	MSG		msg;
	ZeroMemory(&msg , sizeof(msg));

	CWindow* window = CWindow::Instance();

	uint64_t current_time = 0;
	uint64_t last_time = 0;

	CGame& game = CGameManager::GetInstance().GetGame(*this);

	// タイマ解像度をミリ秒に
	::timeBeginPeriod(1);

	while(window->ExecMessage())
	{
		// timeGetTime関数は、ミリ秒単位でシステム時刻を取得します。 
		// システム時間は、Windowsを起動してからの経過時間です。
		current_time = ::timeGetTime();

		uint64_t delta_time = current_time - last_time;

		last_time = current_time;

		if(delta_time != current_time && delta_time < 1000)
		{
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
			//printf("sleep:%f \n", tt);
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(tt)));
			//指定した相対時間だけ現スレッドをブロックする (function template)
		}
	}

	// タイマ解像度を元に戻す
	::timeEndPeriod(1);

	DX11SetTransform::GetInstance()->Uninit();

	// 解放処理
	CDirectXGraphics::GetInstance()->Exit();

	return window->GetMessage();
}

//==============================================================================
//!	@fn		Input
//!	@brief	キー入力
//!	@param	
//!	@retval	
//==============================================================================
void CApplication::Input(uint64_t deltatime)
{}

//==============================================================================
//!	@fn		Update
//!	@brief	更新
//!	@param	
//!	@retval	
//==============================================================================
void CApplication::Update(uint64_t deltatime)
{
	// システムカウンタ
	m_SystemCounter++;
}

//==============================================================================
//!	@fn		Render
//!	@brief	描画
//!	@param	
//!	@retval	
//==============================================================================
void CApplication::Render(uint64_t deltatime)
{}

//==============================================================================
//!	@fn		GetHWnd
//!	@brief	HWND 取得
//!	@param	
//!	@retval	HWND
//==============================================================================
HWND CApplication::GetHWnd()
{
	return m_hWnd;
}

//==============================================================================
//!	@fn		GetHInst
//!	@brief	HINSTANCE 取得
//!	@param	
//!	@retval	HINSTANCE
//==============================================================================
HINSTANCE CApplication::GetHInst()
{
	return m_hInst;
}

//******************************************************************************
//	End of file.
//******************************************************************************
