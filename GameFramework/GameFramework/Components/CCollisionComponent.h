#pragma once

#include "CComponent.h"
#include "../Transform/CTransform.h"

class CCollisionComponent :public CComponent
{
public:
	enum class EType
	{
		AABB,
		SPHERE,
	};

private:
	EType mType;
	CTransform mTransform;
	
	
protected:
	CCollisionComponent(CActor& owner, int priority = 40);

	std::vector<CCollisionComponent*> mColliders;

public:
	virtual ~CCollisionComponent() = 0;
	
	void Update() override;
	const EType& GetType()const { return mType; }
};
