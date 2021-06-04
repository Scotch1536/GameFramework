#include "CComponent.h"

CComponent::CComponent(CActor& owner):mOwnerInterface(owner)
{
	mOwnerInterface.AddComponent(*this);
}