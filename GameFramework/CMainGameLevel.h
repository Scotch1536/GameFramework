#pragma once
#include "GameFramework/Level/CLevel.h"

class CMainGameLevel :public CLevel
{
private:
	float mTime = 60.0f;
	int mScore = 0;

	bool mIsEnd = false;

public:
	using CLevel::CLevel;

	void Init()override;

	void Tick()override;

	void Notice(CActor& actor)override;
};

