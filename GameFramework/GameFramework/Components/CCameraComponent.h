#pragma once
#include <DirectXMath.h>

#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/Memory.h"
#include "../Actor/CActor.h"
#include "../Library/LCMath.h"

#include "CComponent.h"

//!
//! @file
//! @brief �J�����R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

class CSpringArmComponent;

//! @brief �J�����R���|�[�l���g�N���X
class CCameraComponent :public CComponent
{
private:
	XMFLOAT4X4 mView;						//!< �r���[�s��
	XMFLOAT4X4 mCameraTransMatrixBase;		//!< �J�������W�ϊ��s��̃x�[�X
	XMFLOAT4X4 mCameraTransMatrix;			//!< �J�������W�ϊ��s��

	XMFLOAT4X4 mProjection;					//!< �v���W�F�N�V�����s��

	//! @brief �J�����ʒu
	//! �X�v�����O�A�[���ƌq�����Ă���ꍇ�̓^�[�Q�b�g�̃g�����X�t�H�[������̑��΍��W
	//! �X�v�����O�A�[���ƌq�����Ă��Ȃ��ꍇ�͎��g�̃R���|�[�l���g���L�҂̃A�N�^�[�̃g�����X�t�H�[������̑��΍��W
	XMFLOAT3 mEye;
	XMFLOAT3 mLookAt;			//!< �����_
	XMFLOAT3 mUp;				//!< ������x�N�g��

	float mNear;				//!< �j�A�N���b�v
	float mFar;					//!< �t�@�[�N���b�v
	float mAspect;				//!< �A�X�y�N�g��
	float mFov;					//!< ����p

	const CSpringArmComponent* mSpringArm = nullptr;		//!< �X�v�����O�A�[��

	bool mShouldUpdateProjectionMatrix = true;				//!< �v���W�F�N�V�����s����X�V���ׂ���
	bool mShouldUpdateViewMatrix = true;					//!< �r���[�s����X�V���ׂ���

	//! @brief �X�V
	void Update()override;

	//! @brief �r���[�s��X�V
	void UpdateViewMatrix();

	//! @brief �v���W�F�N�V�����s��X�V
	void UpdateProjectionMatrix();

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�̏��L��
	//! @param[in] priority �D��x
	//!
	CCameraComponent(CActor& owner , int priority = 0):CComponent(owner , priority)
	{
		//�s��̏�����
		LCMath::IdentityMatrix(mProjection);
		LCMath::IdentityMatrix(mCameraTransMatrixBase);
		LCMath::IdentityMatrix(mCameraTransMatrix);
		LCMath::IdentityMatrix(mView);
	}

	//!
	//! @brief �r���[���̃Z�b�g
	//! @param[in] eye �J�����́i�ڂ́j�ʒu
	//! @param[in] lookat �����_
	//! @param[in] up ������x�N�g��
	//!
	void SetView(const XMFLOAT3& eye , const XMFLOAT3& lookat , const XMFLOAT3& up)
	{
		SetEye(eye);
		SetLookat(lookat);
		SetUp(up);
	}

	//!
	//! @brief �v���W�F�N�V�������̃Z�b�g
	//! @param[in] nearclip ��A�[�N���b�v
	//! @param[in] farclip �t�@�[�N���b�v
	//! @param[in] fov ����p
	//! @param[in] width ���̃E�B���h�E�T�C�Y
	//! @param[in] height �c�̃E�B���h�E�T�C�Y
	//!
	void SetProjection(float nearclip , float farclip , float fov , float width , float height)
	{
		SetNear(nearclip);
		SetFar(farclip);
		SetFov(fov);
		SetAspect(width , height);
	}

	const XMFLOAT4X4& GetCameraTransMatrixBase()
	{
		return mCameraTransMatrixBase;
	}
	
	const XMFLOAT4X4& GetCameraTransMatrix()
	{
		return mCameraTransMatrix;
	}

	const XMFLOAT4X4& GetViewMatrix()
	{
		return mView;
	}
	
	const XMFLOAT4X4& GetProjectionMatrix()
	{
		return mProjection;
	}

	const XMFLOAT3& GetEye() const
	{
		return mEye;
	}

	const XMFLOAT3& GetLookAt() const
	{
		return mLookAt;
	}

	const XMFLOAT3& GetUp() const
	{
		return mUp;
	}

	const float& GetFov() const
	{
		return mFov;
	}

	const bool& GetShouldUpdateViewMatrix()const
	{
		return mShouldUpdateViewMatrix;
	}

	void SetCameraTransMatrix(const XMFLOAT4X4& mat)
	{
		mCameraTransMatrix = mat;

		//�J�������W�ϊ��s��̋t�s����r���[�s��Ƃ���
		LCMath::InverseMatrix(mCameraTransMatrix , mView);
	}

	void SetNear(float nearclip)
	{
		if(!mShouldUpdateProjectionMatrix)mShouldUpdateProjectionMatrix = true;

		mNear = nearclip;
	}

	void SetFar(float farclip)
	{
		if(!mShouldUpdateProjectionMatrix)mShouldUpdateProjectionMatrix = true;

		mFar = farclip;
	}

	void SetFov(float fov)
	{
		if(!mShouldUpdateProjectionMatrix)mShouldUpdateProjectionMatrix = true;

		mFov = fov;
	}

	void SetAspect(float width , float height)
	{
		if(!mShouldUpdateProjectionMatrix)mShouldUpdateProjectionMatrix = true;

		mAspect = width / height;
	}

	void SetEye(const XMFLOAT3& eye)
	{
		if(!mShouldUpdateViewMatrix)mShouldUpdateViewMatrix = true;

		mEye = eye;
	}

	void SetLookat(const XMFLOAT3& lookat)
	{
		if(!mShouldUpdateViewMatrix)mShouldUpdateViewMatrix = true;

		mLookAt = lookat;
	}

	void SetUp(const XMFLOAT3& up)
	{
		if(!mShouldUpdateViewMatrix)mShouldUpdateViewMatrix = true;

		mUp = up;
	}

	//! @brief �X�v�����O�A�[�����q����
	void JoinSpringArm(const CSpringArmComponent& partner)
	{
		mSpringArm = &partner;
	}
};