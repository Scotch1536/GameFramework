#pragma once
#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Components/CColliderComponent.h"

class CDice :public CActor
{
public:
	CDice(ILevel& owner,XMFLOAT3& pointLocation);

	void Move();
	void Look(CActor& collideActor);
	void EventAtBeginCollide(CActor& collideActor)override;
};

