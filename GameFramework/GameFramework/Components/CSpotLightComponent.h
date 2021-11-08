#pragma once
#include "CPointLightComponent.h"

class CSpotLightComponent :public CPointLightComponent
{
private:
	XMFLOAT3 mDirection;
	float mAngle;

public:
	CSpotLightComponent(CActor& owner, CTransform& parentTrans,
		XMFLOAT4 attenuation, XMFLOAT3 direction, float angle, XMFLOAT3 location);

	const XMFLOAT3 GetDirection()const
	{
		return mDirection;
	}

	const float GetAngle()const
	{
		return mAngle;
	}

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

