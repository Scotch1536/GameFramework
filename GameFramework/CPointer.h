#pragma once
#include "GameFramework/Actor/CActor.h"

class CFighter;

class CPointer :public CActor
{
private:
	CFighter& mOwner;

	float mInitMousePosX;
	float mInitMousePosY;
	float mDiffPosX;
	float mDiffPosY;
public:
	CPointer(ILevel& partner, CFighter& owner);

	void Tick()override;
};

