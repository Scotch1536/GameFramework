#pragma once
#include <Windows.h>
#include <memory>

#include "CLevel.h"

//レベル名
enum class Level
{
	MAX_LEVELNUM ,
};

//ゲームクラス（シングルトン）
class CGame
{
private:
	Level mLevel;
	std::unique_ptr<CLevel> mLevelInfo;

	CGame();

	CGame(const CGame&) = delete;
	CGame& operator=(const CGame&) = delete;
	CGame(CGame&&) = delete;
	CGame& operator=(CGame&&) = delete;

	void LoadLevel();
public:
	static CGame& GetInstance();

	long Execute(HINSTANCE hInst , int winMode)const;

	void Init();	//ゲームの初期化（ウィンドウ作成後に呼び出し）

	void Input(uint64_t deltatime);
	void Update(uint64_t deltatime);
	void Render(uint64_t deltatime);
};

