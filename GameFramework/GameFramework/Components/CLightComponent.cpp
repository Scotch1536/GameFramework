//!
//! @file
//! @brief ���C�g�R���|�[�l���g�̃\�[�X�t�@�C��
//!

#include "CPointLightComponent.h"
#include "CSpotLightComponent.h"

#include "CLightComponent.h"

void CLightComponent::Create(CActor& owner, CTransform& parentTrans, XMFLOAT4 attenuation, XMFLOAT3 location)
{
	//�|�C���g���C�g�쐬
	new CPointLightComponent(owner, parentTrans, attenuation, location);
}

void CLightComponent::Create(CActor& owner, CTransform& parentTrans, XMFLOAT4 attenuation, XMFLOAT3 direction, float angle, XMFLOAT3 location)
{
	//�X�|�b�g���C�g�쐬
	new CSpotLightComponent(owner, parentTrans, attenuation, direction, angle, location);
}
