#include "CComponent.h"
#include "CActor.h"

CComponent::CComponent(IActor& owner , int priority):mPriority(priority)
{
	owner.AddComponent(*this);
}

CComponent::~CComponent() {}