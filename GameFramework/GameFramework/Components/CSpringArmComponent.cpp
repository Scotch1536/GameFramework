//!
//! @file
//! @brief �X�v�����O�A�[���R���|�[�l���g�̃\�[�X�t�@�C��
//!

#include "../Actor/CActor.h"
#include "../Transform/CTransform.h"
#include "../Library/LCMath.h"

#include "CCameraComponent.h"
#include "CSpringArmComponent.h"

CSpringArmComponent::CSpringArmComponent(CActor& owner , const CTransform& targetTrans , CCameraComponent& partnerCamera , ELinkMode linkMode , int priority)
	:CComponent(owner , priority) ,
	mSyncMode(linkMode) ,
	mTargetTransform(targetTrans) ,
	mPartnerCamera(partnerCamera)
{
	//�J�����R���|�[�l���g�ɃX�v�����O�A�[�����q����
	mPartnerCamera.JoinSpringArm(*this);
}

void CSpringArmComponent::IncreaseAlpha()
{
	mAlpha += mIncrementAlpha;

	if(mAlpha > 1.0f)
	{
		mAlpha = 1.0f;
	}
}

void CSpringArmComponent::Update()
{
	XMFLOAT4X4 idealMatrix;

	if(mSyncMode == ELinkMode::ALL_LINK)
	{
		//�p�[�g�i�[�J�����̃J�������W�ϊ��s��̃x�[�X�Ƀ^�[�Q�b�g�̃��[���h�ϊ��s�����Z���邱�ƂŐe�q�֌W�����������̌��ʂ𗝑z�̍s��Ƃ���
		LCMath::CalcMatrixMultply(mPartnerCamera.GetCameraTransMatrixBase() , mTargetTransform.GetWorldMatrix() , idealMatrix);
	}
	else if(mSyncMode == ELinkMode::LOCATION_ONLY_LINK)
	{
		//�p�[�g�i�[�J�����̃J�������W�ϊ��s��̃x�[�X�Ƀ^�[�Q�b�g�̃��P�[�V�����̂݉��Z����
		idealMatrix = mPartnerCamera.GetCameraTransMatrixBase();
		idealMatrix._41 += mTargetTransform.Location.x;
		idealMatrix._42 += mTargetTransform.Location.y;
		idealMatrix._43 += mTargetTransform.Location.z;
	}

	//���z�̍s�񂪂���Ȃ�
	if(mIdealMatrix != nullptr)
	{
		//�O��̗��z�̍s��ƍ���̗��z�̍s�񂪈Ⴄ���A���t�@�l���[���ȊO�Ȃ�
		if(!LCMath::CompareMatrix(*mIdealMatrix , idealMatrix) && mAlpha != 0.0f)
		{
			//���z�̍s��̓���ւ�
			mIdealMatrix.reset(new XMFLOAT4X4(idealMatrix));

			mAlpha = 0.0f;

			return;
		}
	}
	else
	{
		//���z�̍s���ݒ�
		mIdealMatrix.reset(new XMFLOAT4X4(idealMatrix));

		//���z�̍s���V�����J�������W�ϊ��s��Ƃ��ăZ�b�g����
		mPartnerCamera.SetCameraTransMatrix(*mIdealMatrix);

		return;
	}

	//�A���t�@�l�̑���
	IncreaseAlpha();

	//���݂̃p�[�g�i�[�J�����̃J�������W�ϊ��s��Ɨ��z�̍s�����`��Ԃ����̌��ʂ�V�����J�������W�ϊ��s��Ƃ��ăZ�b�g����
	mPartnerCamera.SetCameraTransMatrix(LCMath::Lerp(mPartnerCamera.GetCameraTransMatrix() , *mIdealMatrix , mAlpha));
}