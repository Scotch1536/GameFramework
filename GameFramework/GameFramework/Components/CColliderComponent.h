#pragma once
#include <functional>
#include <unordered_map>

#include "CComponent.h"
#include "../Transform/CTransform.h"

class CTransform;

struct SCollideCacheData
{
	bool IsCollide = false;
	bool IsLastFrameCollide = false;
};

class CColliderComponent :public CComponent
{
public:
	enum class EType
	{
		AABB,
		SPHERE,
	};

private:
	EType mType;

protected:
	std::vector<CColliderComponent*> mColliders;
	std::function<void(CActor&)> mCollisionAction;
	std::unordered_map<CColliderComponent*, SCollideCacheData> mCollideCache;


	bool mShouldCompare = true;

	void ExecuteAction(CActor& argument);
	virtual void ConvertWorldCollider() = 0;

public:
	CTransform Transform;

	CColliderComponent(CActor& owner,CTransform& parentTrans, EType type, int priority = 40);
	virtual ~CColliderComponent();

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
