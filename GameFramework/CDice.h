#pragma once
#include "CActor.h"

class CDice :public CActor
{
public:
	/*
	★超重要★
	コンポーネントの追加は基本的にコンストラクタ内で行う
	*/
	CDice(CLevel& owner);

	void Test();

	void Rot(int dire);
};

