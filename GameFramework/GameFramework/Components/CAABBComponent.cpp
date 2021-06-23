#include "../Library/LCCollision.h"

#include "CAABBComponent.h"

CAABBComponent::CAABBComponent(CActor& owner , int priority):CCollisionComponent(owner , priority)
{}

void CAABBComponent::Update()
{
	CCollisionComponent::Update();

	if(mShouldCompare)
	{
		for(auto collider : mColliders)
		{
			if(collider->GetType() == EType::AABB)
			{
				CAABBComponent& AABBobj = dynamic_cast<CAABBComponent&>(*collider);
				if(LCCollision::Intersect(this->mMin , this->mMax , AABBobj.mMin , AABBobj.mMax))
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
