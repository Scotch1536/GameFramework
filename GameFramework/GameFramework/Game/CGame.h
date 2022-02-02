//!
//!	@file
//!	@brief ゲームシステムのヘッダーファイル
//!

#pragma once
#include <Windows.h>
#include <memory>
#include <functional>

#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/Memory.h"
#include "../Level/CLevel.h"
#include "CApplication.h"

class CLevel;
class CGameManager;
class CApplication;

//! @brief 一般用ゲームインターフェースクラス
class IGame
{
public:
	//! @brief デストラクタ
	virtual ~IGame() {};

	//!
	//! @brief レベルのロード（遷移）
	//! @param[in] level ロードするレベル
	//! @param[in] isFeed フェードするか(フェードアウト)
	//! @param[in] feedColor フェード時の色情報
	//! @param[in] feedTime フェードにかかる秒数
	//!
	virtual void LoadLevel(CLevel& level , bool isFeed = false , XMFLOAT3 feedColor = { 1.0f,1.0f,1.0f } , float feedTime = 1.0f) = 0;
};

//! @brief ゲームマネージャー用ゲームインターフェースクラス
class IGameToGameManager
{
public:
	//! @brief デストラクタ
	virtual ~IGameToGameManager() {};

	//!
	//! @brief 実行
	//! @param[in] hInst インスタンスハンドル
	//! @param[in] winMode ウィンドウモード
	//! @return unsigned long  ウィンドウメッセージ
	//!
	virtual unsigned long Execute(HINSTANCE hInst , int winMode) = 0;

	//!
	//! @brief レベルのセット
	//! @param[in] level セットするレベル
	//!
	virtual void SetLevel(CLevel& level) = 0;

	//!
	//! @brief アプリケーションの取得
	//! @return CApplication アプリケーションシステム
	//!
	virtual CApplication& GetApp() = 0;
};

//! @brief ゲームシステムクラス
class CGame final :public IGame , public IGameToGameManager
{
private:
	//! @brief ビューポート定数バッファ構造体
	ALIGN16 struct SConstantBufferViewPort
	{
		uint32_t ScreenWidth;		//!< スクリーン横幅
		uint32_t ScreenHeight;		//!< スクリーン縦幅
	};

	ComPtr<ID3D11Buffer> mConstantBufferViewPort = nullptr;			//!< ビューポート定数バッファ

	CApplication mApp;												//!< アプリケーション

	std::unique_ptr<CLevel> mLevel;									//!< レベル

	std::function<void()> mLoadLevelEvent;							//!< ロードレベルイベント

	//コピー＆ムーブ禁止
	CGame(const CGame&) = delete;
	CGame& operator=(const CGame&) = delete;
	CGame(CGame&&) = delete;
	CGame& operator=(CGame&&) = delete;

	//!
	//! @brief 実行
	//! @param[in] hInst インスタンスハンドル
	//! @param[in] winMode ウィンドウモード
	//! @return unsigned long  ウィンドウメッセージ
	//!
	unsigned long Execute(HINSTANCE hInst , int winMode)override;

	//!
	//! @brief レベルのセット
	//! @param[in] level セットするレベル
	//!
	void SetLevel(CLevel& level)override;

	//!
	//! @brief レベルのロード（遷移）
	//! @param[in] level ロードするレベル
	//! @param[in] isFeed フェードするか(フェードアウト)
	//! @param[in] feedColor フェード時の色情報
	//! @param[in] feedTime フェードにかかる秒数
	//!
	void LoadLevel(CLevel& level , bool isFeed = false , XMFLOAT3 feedColor = { 1.0f,1.0f,1.0f } , float feedTime = 1.0f)override;

	//!
	//! @brief アプリケーションの取得
	//! @return CApplication アプリケーションシステム
	//!
	CApplication& GetApp()override
	{
		return mApp;
	}

public:
	//! 
	//! @brief コンストラクタ
	//! @param[in] partner このゲームシステムを所有するゲームマネージャー
	//!
	CGame(CGameManager& partner);

	//! @brief デストラクタ
	~CGame();

	//! @brief 初期化（ウィンドウ作成後に呼び出し）
	void Init();

	//! @brief 入力
	void Input();

	//! @brief 更新
	void Update();

	//! @brief 描画
	void Render();

	CLevel& GetLevel()
	{
		return *mLevel;
	}

};

