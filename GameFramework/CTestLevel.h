#pragma once
#include "GameFramework/Level/CLevel.h"

class CTestLevel :public CLevel
{
public:
	/*
	★超重要★
	ゲーム実行時に始めたいレベルはIGameManagerToLevel&を引数にとる
	コンストラクタをオーバーライドする
	*/
	CTestLevel(IGameManagerToLevel& receiver):CLevel(receiver) {};

	/*
	★超重要★
	ゲーム実行時に始めたいレベル以外はCGame&を引数にとる
	コンストラクタをオーバーライドする
	*/
	CTestLevel(CGame& owner):CLevel(owner) {};

	/*
	★超重要★
	アクターの追加は基本ここで行う
	コンポーネント追加することができるが非推奨
	コンポーネントはアクターのコンストラクタで追加することを推奨
	*/
	void Init()override;
};

