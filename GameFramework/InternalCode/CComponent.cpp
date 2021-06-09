#include "CComponent.h"
#include "CActor.h"

CComponent::CComponent(IActor& owner , int priority):mPriority(priority),mOwnerInterface(owner)
{
	mOwnerInterface.AddComponent(*this);
}

CComponent::~CComponent() {}