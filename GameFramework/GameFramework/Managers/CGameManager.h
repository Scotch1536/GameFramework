#pragma once
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
	CGame mGame;			//ゲームクラス

	int64_t mDeltaTime;		//デルタタイム

	bool mCanExecute = true;				//実行できるか
	bool mCanSetStartLevel = true;			//スタートレベルをセットできるか
	bool mIsPause = false;

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
	CGame& GetGame(const Application& partner)
	{
		return mGame;
	}

	const IGame& GetGameInterface()const
	{
		return mGame;
	}

	const bool& GetIsPause()const
	{
		return mIsPause;
	}

	const int64_t& GetDeltaTime()const
	{
		return mDeltaTime;
	}

	void SetIsPause(bool flg)
	{
		mIsPause = flg;
	}

	void SetDeltaTime(const Application& partner , int64_t dt)
	{
		mDeltaTime = dt;
	}
};