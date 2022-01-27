//!
//! @file
//! @brief �J�����A�N�^�[�̃w�b�_�[�t�@�C��
//!

#pragma once
#include "../Components/CCameraComponent.h"
#include "../Game/CApplication.h"

#include "CActor.h"

//! @brief �J�����A�N�^�[�N���X
class CCameraActor :public CActor
{
public:
	CCameraComponent& mCamera;		//!< �J�����R���|�[�l���g�i���֐����d�����p�u���b�N�ݒ�j

	//!
	//! @brief �R���X�g���N�^
	//! @param[in] partner ���̃A�N�^�[�����L���郌�x��
	//!
	CCameraActor(ILevel& partner):CActor(partner) , mCamera(*new CCameraComponent(*this))
	{
		mCamera.SetProjection(10.f , 10000.f , XM_PI / 4.f , CApplication::CLIENT_WIDTH , CApplication::CLIENT_HEIGHT);
		mCamera.SetView({ 0.0f,0.0f,0.0f } , { 0.0f,0.0f,1.0f } , { 0.0f,1.0f,0.0f });
	}
};