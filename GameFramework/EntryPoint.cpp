//!
//!	@file
//!	@brief エントリーポイント
//!	@note アプリケーション開始
//!

#include <Windows.h>
#include "GameFramework/Managers/CGameManager.h"

#include "CTitle.h"

INT APIENTRY WinMain(HINSTANCE  h_hInst ,
	HINSTANCE  h_hPrevInst ,
	LPSTR		h_lpszArgs ,
	int		h_nWinMode)
{
	//ゲームマネージャー取得
	CGameManager& gameManager = CGameManager::GetInstance();

	/*
	★超重要★
	ここに開始したいレベルのコンストラクタを
	引数をIGame&で呼び出す
	メモリ解放はゲームマネージャーが行うので考えなくてよい
	*/
	new CTitle(gameManager.GetGameInterface());

	//ゲームの実行をリクエスト
	gameManager.RequestExecute(h_hInst , h_nWinMode);
}