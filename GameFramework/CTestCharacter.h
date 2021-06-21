#pragma once
#include "GameFramework/Actor/CActor.h"

class CTestCharacter :public CActor
{
public:
	CTestCharacter(ILevel& owner);

private:
	void Move();
	void Rot(int dire);
	void ChangeCameraMove();
	void ChangeCameraMode();
};

