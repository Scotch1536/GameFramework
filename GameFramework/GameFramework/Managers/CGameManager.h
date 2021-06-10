#pragma once
#include <memory>

#include "../Game/CGame.h"

class CLevel;
class CGame;
class IGame;
class Application;

class IGameManagerToLevel
{
public:
	virtual ~IGameManagerToLevel() {};
	virtual void SetStartLevel(CLevel& startLevel) = 0;
};

//ゲームマネージャークラス：シングルトン
class CGameManager :public IGameManagerToLevel
{
private:
	std::unique_ptr<CGame> mGame;			//ゲームクラス

	bool mCanExecute = true;				//実行できるか
	bool mCanSetStartLevel = true;			//スタートレベルをセットできるか

	CGameManager();

	//コピー＆ムーブ禁止
	CGameManager(const CGameManager&) = delete;
	CGameManager& operator=(const CGameManager&) = delete;
	CGameManager(CGameManager&&) = delete;
	CGameManager& operator=(CGameManager&&) = delete;

	//スタートレベルのセット
	void SetStartLevel(CLevel& startLevel)override;
public:
	static CGameManager& GetInstance();

	//実行をリクエスト
	void RequestExecute(HINSTANCE hInst , int winMode);

	//ゲームクラスの取得（アプリケーションクラスの参照が必要）
	CGame& GetGame(Application& partner);

	IGame& GetGameInterface()
	{
		return *mGame;
	}
};