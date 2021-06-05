#include "CComponent.h"
#include "CActor.h"

CComponent::CComponent(CActor& owner):mOwnerInterface(owner)
{
	mOwnerInterface.AddComponent(*this);
}