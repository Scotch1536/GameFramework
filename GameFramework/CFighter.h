//!
//! @file
//! @brief �퓬�@�A�N�^�[�̃w�b�_�[�t�@�C��
//!

#pragma once
#include "GameFramework/Actor/CActor.h"

#include "CPointer.h"

class CParticleSystemComponent;
class CTransform;

//! @brief �퓬�@�A�N�^�[�N���X
class CFighter :public CActor
{
private:
	CPointer& mPointer;			//!< �|�C���^�[

	float mSpeed = 50.0f;		//!< �ړ����x
	float mSpeedLimitMin;		//!< ���x���E�ŏ��l
	float mSpeedLimitMax;		//!< ���x���E�ő�l

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃A�N�^�[�����L���郌�x��
	//!
	CFighter(ILevel& owner);

	//! @brief �ړ�
	void Move();

	//!
	//! @brief ��]
	//! @param[in] dire ����
	//!
	void Rot(int dire);

	//!
	//! @brief ���x�ύX
	//! @param[in] type �^�C�v
	//!
	void SpeedChange(int type);

	//! @brief �e�B�b�N
	void Tick()override;

};