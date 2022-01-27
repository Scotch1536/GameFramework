//!
//! @file
//! @brief ���o�R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <functional>

#include "CComponent.h"
#include "../Transform/CTransform.h"

class CTransform;
class CActor;

//! @brief ���o�R���|�[�l���g�N���X
class CVisionComponent :public CComponent
{
private:
	std::function<void(CActor&)> mEvent;		//!< ���������ɍs����C�x���g

	float mDistance;		//!< ���o�̓͂�����
	float mBaseAngle;		//!< �x�[�X�ƂȂ�p�x�i����p�̔����̃��W�A���j

	//! @brief �X�V
	void Update() override;

public:
	CTransform Transform;		//!< �g�����X�t�H�[��

	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�����L����A�N�^�[
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] distance ���o�̓͂�����
	//! @param[in] fov ����p
	//! @param[in] event ���������ɍs����C�x���g
	//!
	CVisionComponent(CActor& owner, CTransform& parentTrans, float distance, float fov, std::function<void(CActor&)> event);
};