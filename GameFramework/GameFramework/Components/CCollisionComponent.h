#pragma once

#include "CComponent.h"
#include "../Transform/CTransform.h"

class CCollisionComponent :public CComponent
{
public:
	enum class EType
	{
		AABB,
		OBB,
		SPHERE,
	};

private:
	EType mType;
	CTransform mTransform;
	
protected:
	CCollisionComponent(CActor& owner, int priority = 40);

public:
	virtual ~CCollisionComponent() = 0;
	
	void Update() override;
};
