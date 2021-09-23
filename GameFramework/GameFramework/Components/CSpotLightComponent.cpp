#include "CPointLightComponent.h"

#include "CSpotLightComponent.h"

CSpotLightComponent::CSpotLightComponent(CActor& owner, CTransform& parentTrans,
	XMFLOAT4 attenuation, XMFLOAT3 direction, float angle, XMFLOAT3 location = { 0.0f,0.0f,0.0f }) :
	CPointLightComponent(owner,parentTrans,attenuation,location),
	mDirection(direction),
	mAngle(angle)
{
	mType = EType::SPOT;
}