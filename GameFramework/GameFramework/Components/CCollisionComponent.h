#pragma once
#include <functional>
#include <unordered_map>

#include "CComponent.h"
#include "../Transform/CTransform.h"

struct SCollideCacheData
{
	bool IsCollide = false;
	bool IsLastFrameCollide = false;
};

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
	std::vector<CCollisionComponent*> mColliders;
	std::function<void(CActor&)> mCollisionAction;
	std::unordered_map<CCollisionComponent*, SCollideCacheData> mCollideCache;

	bool mShouldCompare = true;

	void ExecuteAction(CActor& argument);
	virtual void ConvertWorldCollider() = 0;

public:
	CCollisionComponent(CActor& owner, int priority = 40);
	virtual ~CCollisionComponent();

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
