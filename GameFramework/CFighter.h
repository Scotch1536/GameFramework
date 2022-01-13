#pragma once
#include <memory>

#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Components/CParticleGeneratorComponent.h"

#include "CPointer.h"

class CParticleSystemComponent;
class CTransform;

class CFighter :public CActor
{
private:
	CPointer& mPointer;

	int mShotCnt = 0;

	float mSpeed = 50.0f;
	float mSpeedLimitMin , mSpeedLimitMax;

public:
	/*
	★超重要★
	コンポーネントの追加は基本的にコンストラクタ内で行う
	*/
	CFighter(ILevel& owner);

	void Shot();
	void ShotReset();
	void Move();
	void Rot(int dire);
	void SpeedChange(int type);

	void Tick()override;
	//void EventAtBeginCollide(CActor& collideActor)override;
	//void EventAtEndCollide(CActor& collideActor)override;

};