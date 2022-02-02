//!
//!	@file
//!	@brief ���[�e�[�^�[�V�X�e���̃w�b�_�[�t�@�C��
//!

#pragma once
#include <memory>
#include <DirectXMath.h>

#include "../Library/LCMath.h"

using namespace DirectX;

class CTransform;

//! @brief ���[�e�[�^�[�N���X
class CRotator
{
private:
	CTransform& mPartner;								//!< ���g�����L����g�����X�t�H�[��

	XMFLOAT4 mQuaternion;								//!< �N�H�[�^�j�I��
	XMFLOAT4 mLastFrameQuaternion;						//!< 1�t���[���O�̃N�H�[�^�j�I��

	bool mIsSameQuaternionToBeforeFrame = true;			//!< 1�t���[���O�̃N�H�[�^�j�I���Ɠ�����

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] partner ���̃��[�e�[�^�[�����L����g�����X�t�H�[��
	//!
	CRotator(CTransform& partner);

	//! @brief �X�V
	void Update();

	//!
	//! @brief �s�񐶐�
	//! @return XMFLOAT4X4 ���������s��
	//!
	XMFLOAT4X4 GenerateMatrix();

	//!
	//! @brief �w��̃��P�[�V�����Ɍ����N�H�[�^�j�I���ɕύX����
	//! @param[in] location �����������P�[�V����
	//!
	void ChangeQuaternionToLocation(XMFLOAT3 location);

	//!
	//! @brief �w��̃��P�[�V�����Ɍ����N�H�[�^�j�I�����Z�o����
	//! @param[in] location �����������P�[�V����
	//! @param[out] result ���ʂ̃N�H�[�^�j�I��
	//!
	void CalcQuaternionToLocation(XMFLOAT3 location , XMFLOAT4& result);

	//!
	//! @brief �p�x�Z�b�g
	//! @param[in] angle �Z�b�g����p�x�i�I�C���[�p�j
	//!
	void SetAngle(const XMFLOAT3& angle);

	//!
	//! @brief �p�x�ǉ��i���[�J���j
	//! @param[in] angle �ǉ�����p�x�i�I�C���[�p�j
	//!
	void AddAngleLocal(const XMFLOAT3& angle);

	//!
	//! @brief �p�x�ǉ��i���[���h�j
	//! @param[in] angle �ǉ�����p�x�i�I�C���[�p�j
	//!
	void AddAngleWorld(const XMFLOAT3& angle);

	const XMFLOAT4& GetQuaternion()const
	{
		return mQuaternion;
	}

	const bool& GetIsSameQuaternionToBeforeFrame()const
	{
		return mIsSameQuaternionToBeforeFrame;
	}

	void SetQuaternion(const XMFLOAT4& qua)
	{
		mQuaternion = qua;
	}

};