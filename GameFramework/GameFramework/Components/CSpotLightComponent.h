//!
//! @file
//! @brief �X�|�b�g���C�g�R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

#pragma once
#include "CPointLightComponent.h"

//! @brief �X�|�b�g���C�g�R���|�[�l���g�N���X
class CSpotLightComponent :public CPointLightComponent
{
private:
	XMFLOAT3 mDirection;		//!< ����
	float mAngle;				//!< �p�x�i�X�|�b�g���C�g�̍L����j

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�����L����A�N�^�[
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] attenuation ������
	//! @param[in] direction ����
	//! @param[in] angle �p�x�i�X�|�b�g���C�g�̍L����j
	//! @param[in] location ���P�[�V����
	//!
	CSpotLightComponent(CActor& owner, CTransform& parentTrans,
		XMFLOAT4 attenuation, XMFLOAT3 direction, float angle, XMFLOAT3 location = { 0.0f,0.0f,0.0f });

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

		//���C�g�}�l�[�W���[�ɒʒm
		CLightManager::GetInstance().Notice();
	}

	void SetAngle(float angle)
	{
		mAngle = angle;

		//���C�g�}�l�[�W���[�ɒʒm
		CLightManager::GetInstance().Notice();
	}

};

