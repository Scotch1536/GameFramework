#include "../Actor/CActor.h"

#include "CComponent.h"

CComponent::CComponent(IActor& owner , int priority):mPriority(priority),mOwnerInterface(owner)
{
	mOwnerInterface.AddComponent(*this);
}

CComponent::~CComponent() {}