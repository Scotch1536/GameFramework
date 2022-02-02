//!
//! @file
//! @brief �J�����R���|�[�l���g�̃\�[�X�t�@�C��
//!

#include "CCameraComponent.h"
#include "CSpringArmComponent.h"

void CCameraComponent::Update()
{
	if(mShouldUpdateProjectionMatrix)
	{
		mShouldUpdateProjectionMatrix = false;

		UpdateProjectionMatrix();		//�v���W�F�N�V�����s��X�V
	}

	if(mShouldUpdateViewMatrix)
	{
		mShouldUpdateViewMatrix = false;

		UpdateViewMatrix();			//�r���[�s��X�V
	}
}

void CCameraComponent::UpdateViewMatrix()
{
	XMFLOAT3 eye;

	//�X�v�����O�A�[�������邩
	if(mSpringArm != nullptr)
	{
		eye = mEye;
	}
	else
	{
		//�J�����ʒu�����[���h���W�n�ɕϊ�����
		XMFLOAT3 pLoc = mOwnerInterface.GetTransform().Location;
		eye = { pLoc.x + mEye.x , pLoc.y + mEye.y , pLoc.z + mEye.z };
	}

	XMFLOAT3 vecX , vecY , vecZ;

	//�J�����ʒu���璍���_�Ɍ������x�N�g����Z���Ƃ���
	LCMath::CalcFloat3FromStartToEnd(eye , mLookAt , vecZ);
	LCMath::CalcFloat3Normalize(vecZ , vecZ);

	//������x�N�g����Z���̊O�ς̌��ʂ�X���Ƃ���
	LCMath::CalcFloat3Cross(mUp , vecZ , vecX);
	LCMath::CalcFloat3Normalize(vecX , vecX);

	//Z����X���̊O�ς̌��ʂ�Y���Ƃ���
	LCMath::CalcFloat3Cross(vecZ , vecX , vecY);
	LCMath::CalcFloat3Normalize(vecY , vecY);

	//�J�������W�ϊ��s��̃x�[�X�̏�����
	mCameraTransMatrixBase._11 = vecX.x;
	mCameraTransMatrixBase._12 = vecX.y;
	mCameraTransMatrixBase._13 = vecX.z;
	mCameraTransMatrixBase._14 = 0.0f;

	mCameraTransMatrixBase._21 = vecY.x;
	mCameraTransMatrixBase._22 = vecY.y;
	mCameraTransMatrixBase._23 = vecY.z;
	mCameraTransMatrixBase._24 = 0.0f;

	mCameraTransMatrixBase._31 = vecZ.x;
	mCameraTransMatrixBase._32 = vecZ.y;
	mCameraTransMatrixBase._33 = vecZ.z;
	mCameraTransMatrixBase._34 = 0.0f;

	mCameraTransMatrixBase._41 = LCMath::CalcFloat3Dot(mEye , vecX);
	mCameraTransMatrixBase._42 = LCMath::CalcFloat3Dot(mEye , vecY);
	mCameraTransMatrixBase._43 = LCMath::CalcFloat3Dot(mEye , vecZ);
	mCameraTransMatrixBase._44 = 1.0f;

	mCameraTransMatrix = mCameraTransMatrixBase;

	//�J�������W�ϊ��s��̋t�s����r���[�s��Ƃ���
	LCMath::InverseMatrix(mCameraTransMatrix , mView);
}

void CCameraComponent::UpdateProjectionMatrix()
{
	ALIGN16 XMMATRIX projection;

	//�v���W�F�N�V�����s��쐬
	projection = XMMatrixPerspectiveFovLH(mFov , mAspect , mNear , mFar);

	//�^�ϊ�
	XMStoreFloat4x4(&mProjection , projection);
}
