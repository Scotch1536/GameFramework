#pragma once
#include <memory>

class CGame;
class IGame;
class Application;

//ゲームマネージャークラス　（シングルトン）
class CGameManager
{
private:
	std::unique_ptr<CGame> mGame;		//ゲームクラス
	bool mCanExecute = true;			//実行できるか

	CGameManager();

	//コピー＆ムーブ禁止
	CGameManager(const CGameManager&) = delete;
	CGameManager& operator=(const CGameManager&) = delete;
	CGameManager(CGameManager&&) = delete;
	CGameManager& operator=(CGameManager&&) = delete;
public:
	static CGameManager& GetInstance();

	//実行をリクエスト
	void RequestExecute(HINSTANCE hInst , int winMode);

	//ゲームクラスの取得（アプリケーションクラスの参照が必要）
	CGame& GetGame(Application& partner);

	IGame& GetGameInterface();
};