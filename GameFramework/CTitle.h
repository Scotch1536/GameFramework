//!
//! @file
//! @brief �^�C�g�����x���̃w�b�_�[�t�@�C��
//!

#pragma once
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Actor/CActor.h"

//! @brief �^�C�g�����x���N���X
class CTitle :public CLevel
{
public:
	using CLevel::CLevel;

	//! @brief ������
	void Init()override;

	//! @brief ���x���̏I��
	void End();
};

