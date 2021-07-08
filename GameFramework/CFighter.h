#pragma once
#include "GameFramework/Actor/CActor.h"

class CFighter :public CActor
{
public:
	bool isHit = false;

	CFighter(ILevel& owner);

	void Move();
	void Rot(int dire);
	void EventAtBeginCollide(CActor& collideActor)override;
	void EventAtEndCollide(CActor& collideActor)override;
};

