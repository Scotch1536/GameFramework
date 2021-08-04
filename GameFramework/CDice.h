#pragma once
#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Components/CColliderComponent.h"

class CDice :public CActor
{
private:
	XMFLOAT3 &mPoint;
public:
	CDice(ILevel& owner,XMFLOAT3& pointLocation);

	void Move();
	void Look(CActor& collideActor);
	void Tick()override;
	void EventAtBeginCollide(CActor& collideActor)override;
};

