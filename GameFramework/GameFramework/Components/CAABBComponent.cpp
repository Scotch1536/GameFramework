#include "../Library/LCCollision.h"

#include "CAABBComponent.h"
#include "../Actor/CActor.h"
#include "../ExternalCode/CModelData.h"

CAABBComponent::CAABBComponent(CActor& owner , const CModelData& model , CTransform& parentTrans , int priority):CColliderComponent(owner , parentTrans , CColliderComponent::EType::AABB , priority)
{
	const std::vector<CMeshData>& meshes = model.GetMeshes();

	for(auto m : meshes)
	{
		for(auto v : m.Vertices)
		{
			if(mLocalMin.x > v.Pos.x)	mLocalMin.x = v.Pos.x;
			else if(mLocalMax.x < v.Pos.x) mLocalMax.x = v.Pos.x;

			if(mLocalMin.y > v.Pos.y)	mLocalMin.y = v.Pos.y;
			else if(mLocalMax.y < v.Pos.y) mLocalMax.y = v.Pos.y;

			if(mLocalMin.z > v.Pos.z)	mLocalMin.z = v.Pos.z;
			else if(mLocalMax.z < v.Pos.z) mLocalMax.z = v.Pos.z;
		}
	}
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
