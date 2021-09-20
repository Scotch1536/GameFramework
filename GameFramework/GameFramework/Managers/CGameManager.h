#pragma once
#include "../Game/CGame.h"

class CLevel;
class CGame;
class IGame;
class CApplication;

//ゲームマネージャークラス：シングルトン
class CGameManager
{
private:
	CGame mGame;			//ゲームクラス

	float mDeltaTime;		//デルタタイム(1秒単位)

	bool mCanExecute = true;				//実行できるか
	bool mCanSetStartLevel = true;			//スタートレベルをセットできるか
	bool mIsPause = false;

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

	//カメラのビュー行列（ポインタ）を取得（カメラがない場合nullptr)
	const XMFLOAT4X4* GetCameraViewMatrix();

	//使用中のカメラとの距離を計算（カメラがない場合0.0f）
	float CalcDistanceToCamera(const XMFLOAT3& compareLocation);

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

	const float& GetDeltaTime()const
	{
		return mDeltaTime;
	}

	void SetIsPause(bool flg)
	{
		mIsPause = flg;
	}

	void SetDeltaTime(const CApplication& partner , int64_t dt)
	{
		mDeltaTime = dt / 1000.0f;
	}

	HWND GetHWnd()
	{
		return static_cast<IGameToGameManager&>(mGame).GetApp().GetHWnd();
	}

};