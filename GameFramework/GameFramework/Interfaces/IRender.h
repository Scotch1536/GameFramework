//!
//!	@file
//!	@brief �����_�[�C���^�[�t�F�[�X�̃w�b�_�[�t�@�C��
//!

#pragma once

//! @brief �����_�[�C���^�[�t�F�[�X�N���X
class IRender
{
public:
	//! @brief �f�X�g���N�^
	virtual ~IRender() {};

	//! @brief �`��
	virtual void Render() = 0;
};
