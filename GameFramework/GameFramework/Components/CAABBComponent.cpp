#include "CAABBComponent.h"
#include "../LCCollision.h"

CAABBComponent::CAABBComponent(CActor& owner, int priority) :CCollisionComponent(owner, priority) 
{

}

void CAABBComponent::Update()
{
	CCollisionComponent::Update();

	for (auto collider : mColliders)
	{
		if (collider->GetType() == EType::AABB)
		{
			CAABBComponent& AABBobj = dynamic_cast<CAABBComponent&>(*collider);
			LCCollision::Intersect(this->mMin, this->mMax, AABBobj.mMin, AABBobj.mMax);
		}
		else if (collider->GetType() == EType::SPHERE)
		{

		}
	}
}
