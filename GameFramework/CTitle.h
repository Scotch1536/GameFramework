#pragma once
#include "GameFramework/Level/CLevel.h"

#include "CTitle.h"

class CTitle :public CLevel
{
public:
	using CLevel::CLevel;

	void End();

	void Init()override;
};

