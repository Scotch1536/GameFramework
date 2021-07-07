#include "../Managers/CColliderManager.h"

#include "CColliderComponent.h"

CColliderComponent::CColliderComponent(CActor& owner , CTransform& parentTrans , EType type , int priority)
	:CComponent(owner , priority) ,
	mType(type) , Transform(parentTrans)
{
	CColliderManager::GetInstance().AddCollider(*this);			//コリジョンマネージャーに追加
}

CColliderComponent::~CColliderComponent()
{
	CColliderManager::GetInstance().ReleaseCollider(*this);
}

void CColliderComponent::ExecuteAction(CActor& argument)
{
	if(mCollisionAction != nullptr)
	{
		mCollisionAction(argument);
	}
}

void CColliderComponent::Update()
{
	if(!CColliderManager::GetInstance().GetColliders(this , mColliders))mShouldCompare = false;
	else mShouldCompare = true;
}

void CColliderComponent::CalcMinMaxOfMeshes(const std::vector<CModelMeshData>& meshes , XMFLOAT3& min , XMFLOAT3& max)
{
	for(auto m : meshes)
	{
		for(auto v : m.Vertices)
		{
			if(min.x > v.Pos.x)	min.x = v.Pos.x;
			else if(max.x < v.Pos.x) max.x = v.Pos.x;

			if(min.y > v.Pos.y)	min.y = v.Pos.y;
			else if(max.y < v.Pos.y) max.y = v.Pos.y;

			if(min.z > v.Pos.z)	min.z = v.Pos.z;
			else if(max.z < v.Pos.z) max.z = v.Pos.z;
		}
	}
}