#pragma once

class CComponent
{
private:
	int mPriority;
public:
	const int& GetPriority()const
	{
		return mPriority;
	}

	virtual void Update() = 0;
};