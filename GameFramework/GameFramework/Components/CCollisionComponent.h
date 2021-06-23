#pragma once
#include <functional>

#include "CComponent.h"
#include "../Transform/CTransform.h"

class CCollisionComponent :public CComponent
{
public:
	enum class EType
	{
		AABB ,
		SPHERE ,
	};

private:
	EType mType;
	CTransform mTransform;

protected:
	std::vector<CCollisionComponent*> mColliders;
	std::function<void(CActor&)> mCollisionAction;

	bool mShouldCompare = true;

	void ExecuteAction(CActor& argument);
public:
	CCollisionComponent(CActor& owner , int priority = 40);
	virtual ~CCollisionComponent() = 0;

	void Update() override;

	void BindCollisionAction(std::function<void(CActor&)> action)
	{
		mCollisionAction = action;
	}

	const EType& GetType()const
	{
		return mType;
	}
};
