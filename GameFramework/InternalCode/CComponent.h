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
};