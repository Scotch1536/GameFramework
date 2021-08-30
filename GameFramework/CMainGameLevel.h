#pragma once
#include "GameFramework/Level/CLevel.h"

class CMainGameLevel :public CLevel
{
public:
	using CLevel::CLevel;

	void Init()override;
};

