#include "../Library/LCCollision.h"
#include "../Library/LCMath.h"
#include "../Actor/CActor.h"
#include "../Data/CModelData.h"

#include "CAABBColliderComponent.h"
#include "CBoxMeshComponent.h"

CAABBColliderComponent::CAABBColliderComponent(CActor& owner , const CModelData& model , CTransform& parentTrans , bool isMesh , int priority)
	:CColliderComponent(owner , parentTrans , CColliderComponent::EType::AABB , priority)
{
	CalcMinMaxOfMeshes(model.GetMeshes() , mLocalMin , mLocalMax);

#ifndef _DEBUG
	isMesh = false;
#endif

	if(isMesh)mBoxMesh = new CBoxMeshComponent(owner , mLocalMin , mLocalMax , { 1.0f,1.0f,1.0f,0.3f });
}

CAABBColliderComponent::CAABBColliderComponent(CActor& owner , XMFLOAT3 min , XMFLOAT3 max , CTransform& parentTrans , bool isMesh , int priority)
	:CColliderComponent(owner , parentTrans , CColliderComponent::EType::AABB , priority)
{
	mLocalMin = min;
	mLocalMax = max;

#ifndef _DEBUG
	isMesh = false;
#endif

	if(isMesh)mBoxMesh = new CBoxMeshComponent(owner , mLocalMin , mLocalMax , { 1.0f,1.0f,1.0f,0.3f });
}

void CAABBColliderComponent::Update()
{
	CColliderComponent::Update();

	if(mShouldCompare)
	{
		ConvertWorldCollider();
		for(auto collider : mColliders)
		{
			if(collider->GetType() == EType::AABB)
			{
				CAABBColliderComponent& AABBobj = dynamic_cast<CAABBColliderComponent&>(*collider);
				if(LCCollision::IsCollide(this->mWorldMin , this->mWorldMax , AABBobj.mWorldMin , AABBobj.mWorldMax))
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

void CAABBColliderComponent::ConvertWorldCollider()
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
