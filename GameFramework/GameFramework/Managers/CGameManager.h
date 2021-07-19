#pragma once
#include "../Game/CGame.h"

class CLevel;
class CGame;
class IGame;
class CApplication;

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

	//カメラのビュー行列を取得
	const XMFLOAT4X4* GetCameraViewMatrix();

	//ゲームクラスの取得（アプリケーションクラスの参照が必要）
	CGame& GetGame(const CApplication& partner)
	{
		return mGame;
	}

	IGame& GetGameInterface()
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

	void SetDeltaTime(const CApplication& partner , int64_t dt)
	{
		mDeltaTime = dt;
	}

	HWND GetHWnd()
	{
		return static_cast<IGameToGameManager&>(mGame).GetApp().GetHWnd();
	}

};