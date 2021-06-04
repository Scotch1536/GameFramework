#pragma once
#include "CActor.h"

class CComponent
{
private:
	int mPriority;
	IActorMethod& mOwnerMethod;
public:
	CComponent(CActor& owner);

	virtual void Update() = 0;

	const int& GetPriority()const
	{
		return mPriority;
	}
};