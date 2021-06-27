#include "../Library/LCCollision.h"

#include "CAABBComponent.h"
#include "../Actor/CActor.h"
#include "../ExternalCode/ModelData.h"

CAABBComponent::CAABBComponent(CActor& owner, const ModelData& model, EType type, int priority) :CCollisionComponent(owner, type, priority)
{
	const std::vector<Mesh>& meshes = model.GetMeshes();

	for (auto m : meshes)
	{
		for (auto v : m.m_vertices)
		{
			if (mLocalMin.x > v.m_Pos.x)	mLocalMin.x = v.m_Pos.x;
			else if (mLocalMax.x < v.m_Pos.x) mLocalMax.x = v.m_Pos.x;

			if (mLocalMin.y > v.m_Pos.y)	mLocalMin.y = v.m_Pos.y;
			else if (mLocalMax.y < v.m_Pos.y) mLocalMax.y = v.m_Pos.y;

			if (mLocalMin.z > v.m_Pos.z)	mLocalMin.z = v.m_Pos.z;
			else if (mLocalMax.z < v.m_Pos.z) mLocalMax.z = v.m_Pos.z;
		}
	}
}

CAABBComponent::CAABBComponent(CActor& owner, XMFLOAT3 min, XMFLOAT3 max, EType type, int priority) : CCollisionComponent(owner, type, priority)
{
	mLocalMin = min;
	mLocalMax = max;
}

void CAABBComponent::Update()
{
	CCollisionComponent::Update();

	if (mShouldCompare)
	{
		ConvertWorldCollider();
		for (auto collider : mColliders)
		{
			if (collider->GetType() == EType::AABB)
			{
				CAABBComponent& AABBobj = dynamic_cast<CAABBComponent&>(*collider);
				if (LCCollision::Intersect(this->mWorldMin, this->mWorldMax, AABBobj.mWorldMin, AABBobj.mWorldMax))
				{
					ExecuteAction(collider->GetOwner());
				}
			}
			else if (collider->GetType() == EType::SPHERE)
			{

			}
		}
	}
}

void CAABBComponent::ConvertWorldCollider()
{
	XMFLOAT3 scale = mOwnerInterface.GetTransform().Scale;
	XMFLOAT3 location = mOwnerInterface.GetTransform().Location;

	mWorldMin.x = (mLocalMin.x * scale.x) + location.x;
	mWorldMin.y = (mLocalMin.y * scale.y) + location.y;
	mWorldMin.z = (mLocalMin.z * scale.z) + location.z;

	mWorldMax.x = (mLocalMax.x * scale.x) + location.x;
	mWorldMax.y = (mLocalMax.y * scale.y) + location.y;
	mWorldMax.z = (mLocalMax.z * scale.z) + location.z;
}
