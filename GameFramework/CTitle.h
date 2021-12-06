#pragma once
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Components/C2DAnimationComponent.h"

#include "CTitle.h"

class CTitle :public CLevel
{
	C2DAnimationComponent* anim;
public:
	using CLevel::CLevel;

	void Test();
	void Test2();

	void End();

	void Init()override;
};

