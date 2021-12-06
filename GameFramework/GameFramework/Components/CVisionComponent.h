#pragma once
#include <functional>

#include "CComponent.h"
#include "../Transform/CTransform.h"

class CTransform;
class CActor;

class CVisionComponent :public CComponent
{
private:
	float mLength;
	float mRadian;
	std::function<void(CActor&)> mEvent;

	void Update() override;

public:
	CTransform Transform;

	CVisionComponent(CActor& owner, CTransform& parentTrans, float length, float angle, std::function<void(CActor&)> event = nullptr, int priority = 90);
};