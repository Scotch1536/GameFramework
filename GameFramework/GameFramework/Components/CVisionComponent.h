#pragma once

#include "CComponent.h"
#include "../Transform/CTransform.h"

class CTransform;

class CVisionComponent :public CComponent
{
private:
	float mLength;
	float mRadian;

	void Update() override;
public:
	CTransform Transform;

	CVisionComponent(CActor& owner,CTransform& parentTrans,float length, float angle,int priority = 90);
};