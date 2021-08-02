#pragma once

#include "CComponent.h"

class CVisionComponent :public CComponent
{
private:
	float mLength;
	float mRadian;

	void Update() override;
public:
	CVisionComponent(CActor& owner,float length, float angle,int priority = 90);
};