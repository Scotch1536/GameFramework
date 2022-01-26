#pragma once
#include "CLightComponent.h"

#include "../Transform/CTransform.h"

//!
//! @file
//! @brief �|�C���g���C�g�R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

class CPointLightComponent : public CLightComponent
{
private:
	XMFLOAT4 mAttenuation;

public:
	CTransform Transform;
	CPointLightComponent(CActor& owner, CTransform& parentTrans,
		XMFLOAT4 attenuation, XMFLOAT3 location = {0.0f,0.0f,0.0f});
	
	const XMFLOAT4 GetAttenuation()const
	{ 
		return mAttenuation; 
	};

	void SetAttenuation(XMFLOAT4 attenuation)
	{
		mAttenuation = attenuation;
		CLightManager::GetInstance().Notice();
	}

};