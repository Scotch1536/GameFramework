//!
//! @file
//! @brief �|�C���^�[�A�N�^�[�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <memory>
#include "GameFramework/Actor/CActor.h"

class CFighter;

//! @brief �|�C���^�[�A�N�^�[�N���X
class CPointer :public CActor
{
private:
	CFighter& mOwner;		//!< ���g�����L����퓬�@

	std::unique_ptr<XMFLOAT3> mInitLocation;		//!< ���������P�[�V����

	float mInitMousePosX;		//!< �������}�E�X���WX
	float mInitMousePosY;		//!< �������}�E�X���WY
	float mDiffPosX;			//!< �������WX
	float mDiffPosY;			//!< �������WY

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃A�N�^�[�����L���郌�x��
	//! @param[in] ownerFighter ���̃A�N�^�[�����L����퓬�@
	//!
	CPointer(ILevel& owner , CFighter& ownerFighter);

	//! @brief �e�B�b�N
	void Tick()override;

};