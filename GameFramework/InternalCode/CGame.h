#pragma once
#include <Windows.h>
#include <memory>

//#include "CGameManager.h"
#include "CLevel.h"
#include "Application.h"

class CLevel;
class CGameManager;

//インターフェース
class IGame
{
public:
	virtual ~IGame() {};
	virtual void LoadLevel(CLevel& level) = 0;
};

//ゲームクラス
class CGame :public IGame
{
private:
	//フレンド指定
	friend CGameManager;

	std::unique_ptr<Application> mApp;		//アプリケーション
	std::unique_ptr<CLevel> mLevel;			//レベル

	CGame();

	//コピー＆ムーブ禁止
	CGame(const CGame&) = delete;
	CGame& operator=(const CGame&) = delete;
	CGame(CGame&&) = delete;
	CGame& operator=(CGame&&) = delete;

	//実行　※このメソッドをエントリーポイントの関数で呼べばウィンドウが作られゲームがスタートする
	long Execute(HINSTANCE hInst , int winMode);

public:
	//レベルのロード（遷移）
	void LoadLevel(CLevel& level)override;

	//ゲームの初期化（ウィンドウ作成後に呼び出し）
	void Init();

	//入力
	void Input(uint64_t deltatime);

	//更新
	void Update(uint64_t deltatime);

	//描画
	void Render(uint64_t deltatime);
};

