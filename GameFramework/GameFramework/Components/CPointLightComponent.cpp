//!
//! @file
//! @brief �|�C���g���C�g�R���|�[�l���g�̃\�[�X�t�@�C��
//!

#include <functional>
#include "../Actor/CActor.h"

#include "CPointLightComponent.h"

CPointLightComponent::CPointLightComponent(CActor& owner, CTransform& parentTrans, XMFLOAT4 attenuation, XMFLOAT3 location) :
	CLightComponent(owner),
	mAttenuation(attenuation),
	Transform(owner, parentTrans)
{
	mType = EType::POINT;
	Transform.Location = location;

	//�g�����X�t�H�[���̍s��X�V�����s�C�x���g�Ɏ��g�̃��\�b�h��ǉ�
	Transform.AddEventWhenMatrixUpdate(std::bind(&CLightManager::Notice, std::ref(CLightManager::GetInstance())));
}