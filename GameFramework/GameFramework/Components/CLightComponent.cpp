#include"CPointLightComponent.h"

#include "CLightComponent.h"

void CLightComponent::Create(CActor& owner, CTransform& parentTrans, XMFLOAT4 attenuation, XMFLOAT3 location)
{
	new CPointLightComponent(owner, parentTrans, attenuation, location);
}