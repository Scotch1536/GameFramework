#pragma once
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Components/C2DAnimationComponent.h"
#include "GameFramework/Actor/CActor.h"

#include "CTitle.h"

class CTitle :public CLevel
{
public:
	CActor* mParticle;

	using CLevel::CLevel;

	//ƒŒƒxƒ‹‚ÌI—¹ˆ—
	void End();

	void Tick()override;

	void Init()override;
};

