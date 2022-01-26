#include "../Actor/CActor.h"

#include "CComponent.h"

//!
//! @file
//! @brief �R���|�[�l���g�̃\�[�X�t�@�C��
//!

CComponent::CComponent(CActor& owner , int priority):mPriority(priority),mOwnerInterface(owner)
{
	//���L�҂̃A�N�^�[�Ɏ��g�̃R���|�[�l���g��ǉ����Ă��炤
	mOwnerInterface.AddComponent(*this);
}

CComponent::~CComponent() {}

CActor& CComponent::GetOwner()const
{
	return mOwnerInterface.GetActor();
}