//!
//!	@file
//!	@brief エントリーポイントのソースファイル
//!

#include <Windows.h>
#include "GameFramework/Managers/CGameManager.h"

#include "CTitle.h"

//!
//! @brief エントリーポイント
//! @param[in] hInst インスタンスハンドル
//! @param[in] hPrevInst 特になし
//! @param[in] lpCmdLine コマンドライン
//! @param[in] winMode ウィンドウモード
//! @return INT 終了コード
//!
INT APIENTRY WinMain(HINSTANCE hInst , HINSTANCE  hPrevInst , LPSTR lpCmdLine , int winMode)
{
	//ゲームマネージャー取得
	CGameManager& gameManager = CGameManager::GetInstance();

	//初期レベルの作成
	new CTitle(gameManager.GetGameInterface());

	//ゲームの実行をリクエスト
	gameManager.RequestExecute(hInst , winMode);
}