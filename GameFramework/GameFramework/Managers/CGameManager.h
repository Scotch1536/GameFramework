//!
//! @file
//! @brief ゲームマネージャーのヘッダーファイル
//!

#pragma once
#pragma comment (lib,"d3d11.lib")					// リンク対象ライブラリ
#pragma comment (lib,"dxgi.lib")					// リンク対象ライブラリ
#pragma comment (lib,"D3DCompiler.lib")				// リンク対象ライブラリ
#pragma comment (lib,"winmm.lib")					// リンク対象ライブラリ
#pragma comment (lib,"dxguid.lib")					// リンク対象ライブラリ
#pragma comment (lib,"dinput8.lib")					// リンク対象ライブラリ

#pragma comment (lib,"assimp-vc141-mtd.lib")		// リンク対象ライブラリ

#ifdef _DEBUG
#pragma comment (lib,"_debug/directxtex.lib")		// リンク対象ライブラリ
#else
#pragma comment (lib,"_release/directxtex.lib")		// リンク対象ライブラリ
#endif

#include "../Game/CGame.h"

class CLevel;
class CGame;
class IGame;
class CApplication;

//! @brief ゲームマネージャークラス
class CGameManager
{
private:
	CGame mGame;								//!< ゲームクラス
	IGameToGameManager* mGameInterface;			//!< ゲームとのインターフェース

	float mDeltaTime;							//!< デルタタイム(1秒単位)

	bool mCanExecute = true;					//!< 実行できるか
	bool mCanSetStartLevel = true;				//!< スタートレベルをセットできるか
	bool mIsPause = false;						//!< ポーズしているか

	//! @brief コンストラクタ
	CGameManager();

	//コピー＆ムーブ禁止
	CGameManager(const CGameManager&) = delete;
	CGameManager& operator=(const CGameManager&) = delete;
	CGameManager(CGameManager&&) = delete;
	CGameManager& operator=(CGameManager&&) = delete;

public:
	//!
	//! @brief インスタンス取得
	//! @return CGameManager& インスタンス
	//!
	static CGameManager& GetInstance();

	//!
	//! @brief 実行をリクエスト
	//! @param[in] hInst インスタンスハンドル
	//! @param[in] winMode ウィンドウモード
	//!
	void RequestExecute(HINSTANCE hInst , int winMode);

	//!
	//! @brief 描画担当カメラのビュー行列取得
	//! @return const XMFLOAT4X4* 描画担当カメラのビュー行列（描画担当カメラが見つからない場合はnullptr）
	//!
	const XMFLOAT4X4* GetCameraViewMatrix();

	//!
	//! @brief 描画担当カメラのロケーション取得
	//! @return XMFLOAT3 描画担当カメラのロケーション（描画担当カメラが見つからない場合は全て0.0f）
	//!
	XMFLOAT3 GetCameraLocation();

	//!
	//! @brief 引数のロケーションと描画担当カメラとの距離を算出
	//! @param[in] compareLocation 描画担当カメラとの距離を比較するロケーション
	//! @return float 結果の距離（描画担当カメラが見つからない場合は比較するロケーションをベクトルとした長さとなる）
	//!
	float CalcDistanceToCamera(const XMFLOAT3& compareLocation);

	//!
	//! @brief ゲームインターフェース取得
	//! @details ゲームシステムをゲームインターフェースにアップキャスト状態（機能を制限した状態）で返す
	//! @return IGame& ゲームインターフェース
	//!
	IGame& GetGameInterface()
	{
		return mGame;
	}

	//!
	//! @brief レベルインターフェース取得
	//! @details レベルをレベルインターフェースにアップキャスト状態（機能を制限した状態）で返す
	//! @return IGame& レベルインターフェース
	//!
	ILevel& GetLevelInterface()
	{
		return mGame.GetLevel();
	}

	//!
	//! @brief ウィンドウハンドル取得
	//! @details ImGui用の措置なので使用は非推奨
	//! @return HWND ウィンドウハンドル
	//!
	HWND GetHWnd()
	{
		return static_cast<IGameToGameManager&>(mGame).GetApp().GetHWnd();
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

	void SetDeltaTime(int64_t dt)
	{
		//秒単位に変換
		mDeltaTime = dt / 1000.0f;
	}

};