#include "../Library/LCCollision.h"
#include "../Library/LCMath.h"
#include "../Actor/CActor.h"
#include "../Data/CModelData.h"

#include "CAABBColliderComponent.h"
#include "CSphereColliderComponent.h"
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

CAABBColliderComponent::CAABBColliderComponent(CActor& owner , CTransform& parentTrans , bool isMesh , int priority)
	:CColliderComponent(owner , parentTrans , CColliderComponent::EType::AABB , priority) ,
	mLocalMin({ -1.0f,-1.0f,-1.0f }) , mLocalMax({ 1.0f,1.0f,1.0f })
{
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
				CAABBColliderComponent& AABBObj = dynamic_cast<CAABBColliderComponent&>(*collider);
				if(LCCollision::IsCollide(mWorldMin , mWorldMax , AABBObj.mWorldMin , AABBObj.mWorldMax))
				{
					ExecuteAction(collider->GetOwner());
				}
			}
			else if(collider->GetType() == EType::SPHERE)
			{
				CSphereColliderComponent& sphereObj = dynamic_cast<CSphereColliderComponent&>(*collider);
				if (LCCollision::IsCollide(mWorldMin, mWorldMax, sphereObj.GetCenter(), sphereObj.GetWorldRadius()))
				{
					ExecuteAction(collider->GetOwner());
				}
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
