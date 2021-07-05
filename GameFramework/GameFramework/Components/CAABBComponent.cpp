#include "../Library/LCCollision.h"

#include "CAABBComponent.h"
#include "../Actor/CActor.h"
#include "../Data/CModelData.h"

CAABBComponent::CAABBComponent(CActor& owner , const CModelData& model , CTransform& parentTrans , int priority):CColliderComponent(owner , parentTrans , CColliderComponent::EType::AABB , priority)
{
	LCCollision::CalcMinMaxOfMeshes(model.GetMeshes(), mLocalMin, mLocalMax);
}

CAABBComponent::CAABBComponent(CActor& owner , XMFLOAT3 min , XMFLOAT3 max , CTransform& parentTrans , int priority): CColliderComponent(owner , parentTrans , CColliderComponent::EType::AABB , priority)
{
	mLocalMin = min;
	mLocalMax = max;
}

void CAABBComponent::Update()
{
	CColliderComponent::Update();

	if(mShouldCompare)
	{
		ConvertWorldCollider();
		for(auto collider : mColliders)
		{
			if(collider->GetType() == EType::AABB)
			{
				CAABBComponent& AABBobj = dynamic_cast<CAABBComponent&>(*collider);
				if(LCCollision::Intersect(this->mWorldMin , this->mWorldMax , AABBobj.mWorldMin , AABBobj.mWorldMax))
				{
					ExecuteAction(collider->GetOwner());
				}
			}
			else if(collider->GetType() == EType::SPHERE)
			{

			}
		}
	}
}

void CAABBComponent::ConvertWorldCollider()
{
	XMFLOAT3 location = Transform.GetWorldLocation();
	XMFLOAT3 scale = Transform.GetWorldScale();

	mWorldMin.x = (mLocalMin.x * scale.x) + location.x;
	mWorldMin.y = (mLocalMin.y * scale.y) + location.y;
	mWorldMin.z = (mLocalMin.z * scale.z) + location.z;

	mWorldMax.x = (mLocalMax.x * scale.x) + location.x;
	mWorldMax.y = (mLocalMax.y * scale.y) + location.y;
	mWorldMax.z = (mLocalMax.z * scale.z) + location.z;
}
