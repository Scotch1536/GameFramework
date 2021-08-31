#pragma once
#include "GameFramework/Level/CLevel.h"

class CMainGameLevel :public CLevel
{
private:
	int mScore = 0;
	float mTime = 60.0f;

public:
	using CLevel::CLevel;

	void Init()override;

	void Tick()override;
};

