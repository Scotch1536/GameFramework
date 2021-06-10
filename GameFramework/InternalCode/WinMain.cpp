//*****************************************************************************
//!	@file	WinMain.cpp
//!	@brief	
//!	@note	アプリケーション開始
//!	@author	
//*****************************************************************************

#pragma comment (lib,"d3d11.lib")					// リンク対象ライブラリ
#pragma comment (lib,"dxgi.lib")					// リンク対象ライブラリ
#pragma comment (lib,"D3DCompiler.lib")				// リンク対象ライブラリ
#pragma comment (lib,"winmm.lib")					// リンク対象ライブラリ
#pragma comment (lib,"directxtex.lib")				// リンク対象ライブラリ
#pragma comment (lib,"dxguid.lib")					// リンク対象ライブラリ
#pragma comment (lib,"dinput8.lib")					// リンク対象ライブラリ
#pragma comment (lib,"assimp-vc141-mtd.lib")		// リンク対象ライブラリ

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include <Windows.h>
#include "CGameManager.h"

#include "../CTestLevel.h"

//==============================================================================
//!	@fn		WinMain
//!	@brief	エントリポイント
//!	@param	インスタンスハンドル
//!	@param	意味なし
//!	@param	起動時の引数文字列
//!	@param	ウインドウ表示モード
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//!	@note	
//==============================================================================
INT APIENTRY WinMain(HINSTANCE  h_hInst,
					 HINSTANCE  h_hPrevInst,
					 LPSTR		h_lpszArgs,
					 int		h_nWinMode)
{
	//ゲームマネージャー取得
	CGameManager& gameManager = CGameManager::GetInstance();

	/*★超重要★
		ここに開始したいレベルのコンストラクタを
		引数をCGameManager&で呼び出す
		メモリ解放はゲームマネージャーが行うので考えなくてよい
		new StartLevelType(CGameManager&);
	*/
	*new CTestLevel(gameManager);

	//ゲームの実行をリクエスト
	gameManager.RequestExecute(h_hInst , h_nWinMode);
}

//******************************************************************************
//	End of file.
//******************************************************************************

	
