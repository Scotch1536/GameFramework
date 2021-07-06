#include "../Library/LCCollision.h"
#include "../Library/LCMath.h"
#include "CSphereColliderComponent.h"
#include "../Actor/CActor.h"
#include "../Data/CModelData.h"
#include "../Components/CSphereMeshComponent.h"

#include "CSphereColliderComponent.h"

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

float CSphereColliderComponent::Distance(const XMFLOAT3& vMax , const XMFLOAT3& vMin)
{
	XMVECTOR vector1 = XMLoadFloat3(&vMax);
	XMVECTOR vector2 = XMLoadFloat3(&vMin);
	XMVECTOR vectorSub = DirectX::XMVectorSubtract(vector1 , vector2);
	XMVECTOR length = DirectX::XMVector3Length(vectorSub);

	float distance = 0.0f;
	XMStoreFloat(&distance , length);
	return distance;
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
				if(LCCollision::Intersect(this->mWorldPosition , this->mRadius , Sphereobj.mWorldPosition , Sphereobj.mRadius))
				{
					ExecuteAction(collider->GetOwner());
				}
			}
			else if(collider->GetType() == EType::AABB)
			{

			}
		}
	}
}

void CSphereColliderComponent::ConvertWorldCollider()
{
	mWorldPosition = Transform.GetWorldLocation();
	//mWorldPosition.y = Transform.GetWorldLocation().y;
	//mWorldPosition.z = Transform.GetWorldLocation().z;
}
