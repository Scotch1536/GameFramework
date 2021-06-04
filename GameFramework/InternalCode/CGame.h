#pragma once
#include <Windows.h>
#include <memory>

#include "CLevel.h"

class IGameMethod
{
public:
	virtual ~IGameMethod() {};
	virtual void LoadLevel(CLevel& level) = 0;
};

//ゲームクラス（シングルトン）
class CGame:public IGameMethod
{
private:
	std::unique_ptr<CLevel> mLevel;

	CGame();

	CGame(const CGame&) = delete;
	CGame& operator=(const CGame&) = delete;
	CGame(CGame&&) = delete;
	CGame& operator=(CGame&&) = delete;

public:
	static CGame& GetInstance();

	//実行　※このメソッドをエントリーポイントの関数で呼べばウィンドウが作られゲームがスタートする
	long Execute(HINSTANCE hInst , int winMode)const;

	void Init();	//ゲームの初期化（ウィンドウ作成後に呼び出し）

	void Input(uint64_t deltatime);
	void Update(uint64_t deltatime);
	void Render(uint64_t deltatime);

	//レベルのロード（遷移）
	void LoadLevel(CLevel& level)override;
};

