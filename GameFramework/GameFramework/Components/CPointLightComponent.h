#pragma once
#include "CLightComponent.h"

#include "../Transform/CTransform.h"
class CPointLightComponent : public CLightComponent
{
private:

	XMFLOAT4 mAttenuation;

public:
	CTransform Transform;
	CPointLightComponent(CActor& owner, CTransform& parentTrans, XMFLOAT4 attenuation, XMFLOAT3 location = {0.0f,0.0f,0.0f});
	
	void Update()
	{

	}

	void SetAttenuation(XMFLOAT4 attenuation)
	{
		mAttenuation = attenuation;
		CLightManager::GetInstance().Notice();
	}
};