#pragma once
#include <memory>
#include "GameFramework/Actor/CActor.h"
#include "CPointer.h"

class CFighter :public CActor
{
private:
	CPointer& mPointer;
	std::unique_ptr<XMFLOAT4> mTargetRot;
	bool mIsHit = false;

public:
	CFighter(ILevel& owner);

	void Move();
	void Rot();
	void EventAtBeginCollide(CActor& collideActor)override;
	void EventAtEndCollide(CActor& collideActor)override;
	//void Tick()override;

	bool GetIsHit()const
	{
		return mIsHit;
	}
};

