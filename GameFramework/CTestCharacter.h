#pragma once
#include "GameFramework/Actor/CActor.h"

class CTestCharacter :public CActor
{
public:
	CTestCharacter(ILevel& owner);

private:
	void Move(int num);
	void Rot(int dire);
	void ChangeCameraMove();
	void ChangeCameraMode();
	void CollisionAction(CActor& collideActor);
};

