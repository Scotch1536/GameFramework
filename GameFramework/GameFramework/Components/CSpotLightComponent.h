#pragma once
#include "CPointLightComponent.h"

class CSpotLightComponent :public CPointLightComponent
{
private:

	XMFLOAT3 mDirection;
	float mAngle;

public:
	CSpotLightComponent(CActor& owner, CTransform& parentTrans,
		XMFLOAT4 attenuation,XMFLOAT3 direction,float angle, XMFLOAT3 location = { 0.0f,0.0f,0.0f });

	void SetDirection(XMFLOAT3 direction)
	{
		mDirection = direction;
		CLightManager::GetInstance().Notice();
	}

	void SetAngle(float angle)
	{
		mAngle = angle;
		CLightManager::GetInstance().Notice();
	}
};
