#pragma once
#include "GameFramework/Actor/CActor.h"

class CBullet :public CActor
{
private:
	XMFLOAT3 mDirection;
	int mDestroyFrame;
	int mFrame = 0;

public:
	CBullet(ILevel& partner , XMFLOAT3 initLocation , XMFLOAT3 direction , int destroyFrame);

	void Tick()override;
	void EventAtBeginCollide(CActor& collideActor)override;
};

