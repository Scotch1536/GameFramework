#include "../Library/LCCollision.h"
#include "../Actor/CActor.h"
#include "../ExternalCode/CModelData.h"
#include "../Components/CSphereMeshComponent.h"

#include "CSphereColliderComponent.h"

CSphereColliderComponent::CSphereColliderComponent(CActor& owner , const CModelData& model , CTransform& parentTrans , bool isMesh , int priority)
	:CColliderComponent(owner , parentTrans , CColliderComponent::EType::SPHERE , priority)
{
	const std::vector<CMeshData>& meshes = model.GetMeshes();
	XMFLOAT3 mMin = { 0,0,0 };
	XMFLOAT3 mMax = { 0,0,0 };

	for(auto m : meshes)
	{
		for(auto v : m.Vertices)
		{
			if(mMin.x > v.Pos.x)	mMin.x = v.Pos.x;
			else if(mMax.x < v.Pos.x) mMax.x = v.Pos.x;

			if(mMin.y > v.Pos.y)	mMin.y = v.Pos.y;
			else if(mMax.y < v.Pos.y) mMax.y = v.Pos.y;

			if(mMin.z > v.Pos.z)	mMin.z = v.Pos.z;
			else if(mMax.z < v.Pos.z) mMax.z = v.Pos.z;
		}
	}
	mRadius = Distance(mMax , mMin)/2;

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
