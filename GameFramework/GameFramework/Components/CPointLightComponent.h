//!
//! @file
//! @brief �|�C���g���C�g�R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

#pragma once
#include "CLightComponent.h"

#include "../Transform/CTransform.h"

//! @brief �|�C���g���C�g�R���|�[�l���g�N���X
class CPointLightComponent : public CLightComponent
{
private:
	XMFLOAT4 mAttenuation;		//!< ������

public:
	CTransform Transform;		//!< �g�����X�t�H�[��

	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�����L����A�N�^�[
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] attenuation ������
	//! @param[in] location ���P�[�V����
	//!
	CPointLightComponent(CActor& owner, CTransform& parentTrans,
		XMFLOAT4 attenuation, XMFLOAT3 location = {0.0f,0.0f,0.0f});
	
	const XMFLOAT4 GetAttenuation()const
	{ 
		return mAttenuation; 
	};

	void SetAttenuation(XMFLOAT4 attenuation)
	{
		mAttenuation = attenuation;

		//���C�g�}�l�[�W���[�ɒʒm
		CLightManager::GetInstance().Notice();
	}

};