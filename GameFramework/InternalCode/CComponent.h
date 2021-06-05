#pragma once

class IActor;
class CActor;

class CComponent
{
private:
	int mPriority;
	IActor& mOwnerInterface;
public:
	CComponent(CActor& owner);

	virtual void Update() = 0;

	const int& GetPriority()const
	{
		return mPriority;
	}
};