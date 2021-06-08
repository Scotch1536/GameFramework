#pragma once
#include "CLevel.h"

class CTestLevel :public CLevel
{
public:
	CTestLevel(CGameManager& receiver):CLevel(receiver) {};

	void Init()override;
};

