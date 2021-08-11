#include "../Actor/CActor.h"
#include "../Managers/CColliderManager.h"
#include "../Library/LCCollision.h"

#include "CColliderComponent.h"
#include "CSphereColliderComponent.h"
#include "CAABBColliderComponent.h"

CColliderComponent::CColliderComponent(CActor& owner , CTransform& parentTrans , EType type , int priority)
	:CComponent(owner , priority) ,
	mType(type) , mEventAtBeginningCollided(std::bind(&CActor::EventAtBeginCollide , std::ref(owner) , std::placeholders::_1)) ,
	mEventAtEndCollided(std::bind(&CActor::EventAtEndCollide , std::ref(owner) , std::placeholders::_1)) ,
	Transform(parentTrans)
{
	CColliderManager::GetInstance().AddCollider(*this);			//コリジョンマネージャーに追加
}

CColliderComponent::~CColliderComponent()
{
	CColliderManager::GetInstance().ReleaseCollider(*this);
}

void CColliderComponent::UpdateCollidedCache(CColliderComponent* target , bool isCollided)
{
	if(mCollidedCache.count(target) == 0)
	{
		mCollidedCache[target];
	}

	mCollidedCache[target].IsLastFrameCollide = mCollidedCache[target].IsCollide;
	mCollidedCache[target].IsCollide = isCollided;

	if(mCollidedCache[target].IsCollide == true && mCollidedCache[target].IsLastFrameCollide == false)
	{
		mEventAtBeginningCollided(target->GetOwner());
	}
	else if(mCollidedCache[target].IsCollide == false && mCollidedCache[target].IsLastFrameCollide == true)
	{
		mEventAtEndCollided(target->GetOwner());
	}
}

void CColliderComponent::Update()
{
	if(!CColliderManager::GetInstance().GetColliders(this , mColliders))mShouldCompared = false;
	else mShouldCompared = true;

	if(mShouldCompared)
	{
		if(mType == EType::AABB)
		{
			CAABBColliderComponent& thisObj = dynamic_cast<CAABBColliderComponent&>(*this);
			for(auto& collider : mColliders)
			{
				if(mObjectType != "NONE" && mObjectType == collider->mObjectType)
				{
					continue;
				}

				if(collider->GetType() == EType::AABB)
				{
					CAABBColliderComponent& AABBObj = dynamic_cast<CAABBColliderComponent&>(*collider);
					if(LCCollision::IsCollide(thisObj.GetWorldMin() , thisObj.GetWorldMax() , AABBObj.GetWorldMin() , AABBObj.GetWorldMax()))
					{
						UpdateCollidedCache(collider , true);
					}
					else UpdateCollidedCache(collider , false);
				}
				else if(collider->GetType() == EType::SPHERE)
				{
					CSphereColliderComponent& sphereObj = dynamic_cast<CSphereColliderComponent&>(*collider);
					if(LCCollision::IsCollide(thisObj.GetWorldMin() , thisObj.GetWorldMax() , sphereObj.GetCenter() , sphereObj.GetWorldRadius()))
					{
						UpdateCollidedCache(collider , true);
					}
					else UpdateCollidedCache(collider , false);
				}
			}
		}
		else if(mType == EType::SPHERE)
		{
			CSphereColliderComponent& thisObj = dynamic_cast<CSphereColliderComponent&>(*this);
			for(auto& collider : mColliders)
			{
				if(mObjectType != "NONE"&&mObjectType == collider->mObjectType)
				{
					continue;
				}

				if(collider->GetType() == EType::AABB)
				{
					CAABBColliderComponent& AABBObj = dynamic_cast<CAABBColliderComponent&>(*collider);
					if(LCCollision::IsCollide(AABBObj.GetWorldMin() , AABBObj.GetWorldMax() , thisObj.GetCenter() , thisObj.GetWorldRadius()))
					{
						UpdateCollidedCache(collider , true);
					}
					else UpdateCollidedCache(collider , false);
				}
				else if(collider->GetType() == EType::SPHERE)
				{
					CSphereColliderComponent& Sphereobj = dynamic_cast<CSphereColliderComponent&>(*collider);
					if(LCCollision::IsCollide(thisObj.GetCenter() , thisObj.GetWorldRadius() , Sphereobj.GetCenter() , Sphereobj.GetWorldRadius()))
					{
						UpdateCollidedCache(collider , true);
					}
					else UpdateCollidedCache(collider , false);
				}
			}
		}
	}
}

void CColliderComponent::CalcMinMaxOfMeshes(const std::vector<CModelMeshData>& meshes , XMFLOAT3& min , XMFLOAT3& max)
{
	for(auto& m : meshes)
	{
		for(auto& v : m.Vertices)
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