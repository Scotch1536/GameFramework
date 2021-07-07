#include "../Library/LCCollision.h"
#include "../Library/LCMath.h"
#include "../Actor/CActor.h"
#include "../Data/CModelData.h"

#include "CAABBColliderComponent.h"
#include "CSphereColliderComponent.h"
#include "CSphereMeshComponent.h"

CSphereColliderComponent::CSphereColliderComponent(CActor& owner , const CModelData& model , CTransform& parentTrans , bool isMesh , int priority)
	:CColliderComponent(owner , parentTrans , CColliderComponent::EType::SPHERE , priority)
{
	XMFLOAT3 min = { 0,0,0 };
	XMFLOAT3 max = { 0,0,0 };

	CalcMinMaxOfMeshes(model.GetMeshes() , min , max);

	XMFLOAT3 vec;
	float length;

	LCMath::CalcFloat3FromStartToGoal(min , max , vec);
	LCMath::CalcFloat3Length(vec , length);

	mRadius = length / 2.0f;

#ifndef _DEBUG
	isMesh = false;
#endif

	if(isMesh)mSphereMesh = new CSphereMeshComponent(owner , mRadius , 50 , { 1.0f,1.0f,1.0f,0.3f });
}

CSphereColliderComponent::CSphereColliderComponent(CActor& owner , float radius , CTransform& parentTrans , bool isMesh , int priority)
	:CColliderComponent(owner , parentTrans , CColliderComponent::EType::SPHERE , priority)
{
	mRadius = radius;

#ifndef _DEBUG
	isMesh = false;
#endif

	if(isMesh)mSphereMesh = new CSphereMeshComponent(owner , mRadius , 50 , { 1.0f,1.0f,1.0f,0.3f });
}

void CSphereColliderComponent::Update()
{
	CColliderComponent::Update();

	if(mShouldCompare)
	{
		ConvertWorldCollider();
		for(auto collider : mColliders)
		{
			if(collider->GetType() == EType::SPHERE)
			{
				CSphereColliderComponent& Sphereobj = dynamic_cast<CSphereColliderComponent&>(*collider);
				if(LCCollision::IsCollide(mWorldLocation , mRadius , Sphereobj.mWorldLocation , Sphereobj.mRadius))
				{
					ExecuteAction(collider->GetOwner());
				}
			}
			else if(collider->GetType() == EType::AABB)
			{
				CAABBColliderComponent& AABBObj = dynamic_cast<CAABBColliderComponent&>(*collider);
				if (LCCollision::IsCollide(AABBObj.GetWorldMin(), AABBObj.GetWorldMax(),mWorldLocation,mRadius))
				{
					ExecuteAction(collider->GetOwner());
				}
			}
		}
	}
}

void CSphereColliderComponent::ConvertWorldCollider()
{
	mWorldLocation = Transform.GetWorldLocation();
}
