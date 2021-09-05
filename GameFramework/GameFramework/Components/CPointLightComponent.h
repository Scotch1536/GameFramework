#pragma once
#include "CLightComponent.h"

class CPointLightComponent : public CLightComponent
{
private:

	XMFLOAT4 mLightPos;
	XMFLOAT4 mAttenuation;

public:

	void SetLightPos(XMFLOAT4 pos)
	{
		mLightPos = pos;
	}

	void SetAttenuation(XMFLOAT4 attenuation)
	{
		mAttenuation = attenuation;
	}
};