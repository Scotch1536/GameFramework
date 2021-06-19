#pragma once

#include "CComponent.h"

class CCollisionComponent :public CComponent
{
public:
	enum class Type
	{
		AABB,
		OBB,
		SPHERE,
	};

private:
	Type mType;
	bool mFlg;

public:
	CCollisionComponent(CActor& owner, int priority = 40) :CComponent(owner, priority) {}
};
