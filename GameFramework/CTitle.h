#pragma once
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Components/C2DAnimationComponent.h"
#include "GameFramework/Actor/CActor.h"

#include "CTitle.h"

class CTitle :public CLevel
{
public:
	CActor* mParticle;
	int mCounter;

	using CLevel::CLevel;

	//���x���̏I������
	void End();

	void Tick()override;

	void Init()override;
};

