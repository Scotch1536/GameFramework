#include "CComponent.h"


CComponent::CComponent(CActor& owner):mOwnerMethod(owner)
{
	mOwnerMethod.AddComponent(*this);
}