//!
//!	@file
//!	@brief アプリケーションシステムのヘッダーファイル
//!

#pragma once

#include	<Windows.h>
#include	<stdio.h>
#include	<cinttypes>

class CGame;

//! @brief アプリケーションクラス
class CApplication
{
public:
	static const char* WINDOW_TITLE;						//!< ウィンドウタイトル
	static const char* WINDOW_CLASS_NAME;					//!< ウィンドウクラス名

	static const uint32_t WINDOW_STYLE_WINDOWED;			//!< ウィンドウスタイル
	static const uint32_t WINDOW_EX_STYLE_WINDOWED;			//!< ウィンドウスタイルEX
	static const uint32_t WINDOW_STYLE_FULL_SCREEN;			//!< ウィンドウスタイルフルスクリーン
	static const uint32_t WINDOW_EX_STYLE_FULL_SCREEN;		//!< ウィンドウスタイルEXフルスクリーン

	static const uint32_t CLIENT_WIDTH;						//!< ウィンドウ横幅
	static const uint32_t CLIENT_HEIGHT;					//!< ウィンドウ縦幅

	static const float FPS;									//!< FPS

private:
	HWND mHWnd;					//!< Windowハンドル
	HINSTANCE mHInstance;		//!< インスタンスハンドル
	CGame* mGame;				//!< ゲームシステム

	//コピー禁止
	CApplication(const CApplication&);
	CApplication& operator= (const CApplication&) {}

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] partner このアプリケーションを所有するゲームシステム
	//!
	CApplication(CGame& partner):mGame(&partner) {};

	//!
	//! @brief 初期化
	//! @param[in] hInstance インスタンスハンドル
	//!
	void Init(HINSTANCE hInstance);

	//!
	//! @brief メインループ
	//! @return unsigned long ウィンドウメッセージ
	//!
	unsigned long MainLoop();

	HWND GetHWnd()const
	{
		return mHWnd;
	}

	HINSTANCE GetHInst()const
	{
		return mHInstance;
	}

};