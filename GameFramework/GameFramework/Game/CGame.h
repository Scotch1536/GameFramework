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
	virtual void LoadLevel(CLevel& level) = 0;
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
	ALIGN16 struct ConstantBufferViewPort
	{
		uint32_t ScreenWidth;
		uint32_t ScreenHeight;
	};

	ComPtr<ID3D11Buffer> mConstantBufferViewPort = nullptr;		//定数バッファ

	CApplication mApp;		//アプリケーション

	std::unique_ptr<CLevel> mLevel;			//レベル
	
	std::function<void()> mLoadLevelFunction;			//ロードレベル関数オブジェクト


	//コピー＆ムーブ禁止
	CGame(const CGame&) = delete;
	CGame& operator=(const CGame&) = delete;
	CGame(CGame&&) = delete;
	CGame& operator=(CGame&&) = delete;

	//実行　※このメソッドをエントリーポイントの関数で呼べばウィンドウが作られゲームがスタートする
	long Execute(HINSTANCE hInst , int winMode)override;

	void SetLevel(CLevel& level)override;

	//レベルのロード（遷移）
	void LoadLevel(CLevel& level)override;

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

	const CLevel& GetLevel()
	{
		return *mLevel;
	}
};

