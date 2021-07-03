#include "../Library/LCCollision.h"
#include "../Actor/CActor.h"
#include "../ExternalCode/ModelData.h"
#include "../Components/CSphereMeshComponent.h"

#include "CSphereColliderComponent.h"

CSphereColliderComponent::CSphereColliderComponent(CActor& owner , const ModelData& model , CTransform& parentTrans , bool isMesh , int priority)
	:CColliderComponent(owner , parentTrans , CColliderComponent::EType::SPHERE , priority)
{
	const std::vector<Mesh>& meshes = model.GetMeshes();
	XMFLOAT3 mMin = { 0,0,0 };
	XMFLOAT3 mMax = { 0,0,0 };

	for(auto m : meshes)
	{
		for(auto v : m.m_vertices)
		{
			if(mMin.x > v.m_Pos.x)	mMin.x = v.m_Pos.x;
			else if(mMax.x < v.m_Pos.x) mMax.x = v.m_Pos.x;

			if(mMin.y > v.m_Pos.y)	mMin.y = v.m_Pos.y;
			else if(mMax.y < v.m_Pos.y) mMax.y = v.m_Pos.y;

			if(mMin.z > v.m_Pos.z)	mMin.z = v.m_Pos.z;
			else if(mMax.z < v.m_Pos.z) mMax.z = v.m_Pos.z;
		}
	}
	mRadius = Distance(mMax , mMin)/2;

	if(isMesh)mSphereMesh = new CSphereMeshComponent(owner , mRadius , 50 , { 1.0f,1.0f,1.0f,0.3f });
}

CSphereColliderComponent::CSphereColliderComponent(CActor& owner , float radius , CTransform& parentTrans , bool isMesh , int priority)
	:CColliderComponent(owner , parentTrans , CColliderComponent::EType::SPHERE , priority)
{
	mRadius = radius;

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
	mWorldPosition.x = Transform.GetWorldMatrixResult()._41;
	mWorldPosition.y = Transform.GetWorldMatrixResult()._42;
	mWorldPosition.z = Transform.GetWorldMatrixResult()._43;
}
