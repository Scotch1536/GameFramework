#include "CComponent.h"
#include "CActor.h"

CComponent::CComponent(IActor& owner)
{
	owner.AddComponent(*this);
}