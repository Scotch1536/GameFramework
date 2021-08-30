#pragma once
#include "GameFramework/Actor/CActor.h"

class CAttachObject :public CActor
{
public:
	CAttachObject(ILevel& partner);
	
	void EventAtBeginCollide(CActor& collideActor)override;
};

