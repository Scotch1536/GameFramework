#include "../Actor/CActor.h"

#include "CComponent.h"

CComponent::CComponent(CActor& owner , int priority):mPriority(priority),mOwnerInterface(owner)
{
	mOwnerInterface.AddComponent(*this);
}

CComponent::~CComponent() {}

CActor& CComponent::GetOwner()const
{
	return mOwnerInterface.GetActor();
}