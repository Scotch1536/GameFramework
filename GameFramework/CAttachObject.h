//!
//! @file
//! @brief �A�^�b�`�I�u�W�F�N�g�A�N�^�[�̃w�b�_�[�t�@�C��
//!

#pragma once
#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Components/CPrimitiveMeshComponent.h"

//! @brief �A�^�b�`�I�u�W�F�N�g�A�N�^�[�N���X
class CAttachObject :public CActor
{
private:
	CPrimitiveMeshComponent<>* mMesh = nullptr;			//!< ���b�V��

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃A�N�^�[�����L���郌�x��
	//!
	CAttachObject(ILevel& owner);

	//!
	//! @brief �ՓˊJ�n�C�x���g
	//! @param[in] collideActor ���������A�N�^�[
	//!
	void EventAtBeginCollide(CActor& collideActor)override;
};

