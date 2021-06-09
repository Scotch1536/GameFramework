#pragma once
#include "CLevel.h"

class CTestLevel :public CLevel
{
public:
	CTestLevel(IGameManagerToLevel& receiver):CLevel(receiver) {};

	void Init()override;
};

