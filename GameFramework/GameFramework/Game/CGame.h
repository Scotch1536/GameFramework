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

//インターフェース
class IGame
{
public:
	virtual ~IGame() {};
	virtual void LoadLevel(CLevel& level , bool isFeed = false , XMFLOAT3 feedColor = { 1.0f,1.0f,1.0f } , float feedTime = 1.0f) = 0;
};

class IGameToGameManager
{
public:
	virtual ~IGameToGameManager() {};
	virtual void SetLevel(CLevel& level) = 0;
	virtual long Execute(HINSTANCE hInst , int winMode) = 0;
	virtual CApplication& GetApp() = 0;
};

//ゲームクラス
class CGame :public IGame , public IGameToGameManager
{
private:
	//ビューポート定数バッファ構造体
	ALIGN16 struct SConstantBufferViewPort
	{
		uint32_t ScreenWidth;
		uint32_t ScreenHeight;
	};

	ComPtr<ID3D11Buffer> mConstantBufferViewPort = nullptr;		//ビューポート定数バッファ

	CApplication mApp;		//アプリケーション

	std::unique_ptr<CLevel> mLevel;			//レベル

	std::function<void()> mLoadLevelFunction;			//ロードレベルの関数を格納しておく関数オブジェクト

	//コピー＆ムーブ禁止
	CGame(const CGame&) = delete;
	CGame& operator=(const CGame&) = delete;
	CGame(CGame&&) = delete;
	CGame& operator=(CGame&&) = delete;

	//ゲームフローの実行
	long Execute(HINSTANCE hInst , int winMode)override;

	//レベルのセット
	void SetLevel(CLevel& level)override;

	//レベルのロード（レベルの遷移、変更）
	void LoadLevel(CLevel& level , bool isFeed = false , XMFLOAT3 feedColor = { 1.0f,1.0f,1.0f } , float feedTime = 1.0f)override;

	CApplication& GetApp()override
	{
		return mApp;
	}

public:
	CGame(CGameManager& partner);
	~CGame();

	//ゲームの初期化（ウィンドウ作成後に呼び出し）
	void Init();

	//入力
	void Input();

	//更新
	void Update();

	//描画
	void Render();

	CLevel& GetLevel()
	{
		return *mLevel;
	}
};

