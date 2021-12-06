#pragma once
#include <DirectXMath.h>

#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/Memory.h"
#include "../Actor/CActor.h"
#include "../Library/LCMath.h"

#include "CComponent.h"

class CSpringArmComponent;

class CCameraComponent :public CComponent
{
private:
	XMFLOAT4X4 mProjection;		//�v���W�F�N�V�����s��

	XMFLOAT4X4 mView;			//�r���[�s��

	XMFLOAT3 mEye;				//�J�����ʒu(���΍��W)
	XMFLOAT3 mLookAt;			//�����_
	XMFLOAT3 mUp;				//������x�N�g��

	float mNear;				//�j�A�N���b�v
	float mFar;					//�t�@�[�N���b�v
	float mAspect;				//�A�X�y�N�g��
	float mFov;					//����p

	const CSpringArmComponent* mSpringArm = nullptr;		//�X�v�����O�A�[��

	bool mShouldUpdateProjectionMatrix = true;		//�v���W�F�N�V�����s����X�V���ׂ���
	bool mShouldUpdateViewMatrix = true;			//�r���[�s����X�V���ׂ���

	//�v���W�F�N�V�����s��쐬
	void CreateProjectionMatrix();

	//�r���[�s��쐬
	void CreateViewMatrix();

	//�X�V
	void Update()override;

public:
	CCameraComponent(CActor& owner , int priority = 80):CComponent(owner , priority)
	{
		LCMath::IdentityMatrix(mProjection);
		LCMath::IdentityMatrix(mView);
	}

	void SetProjection(float nearclip , float farclip , float fov , float width , float height)
	{
		SetNear(nearclip);
		SetFar(farclip);
		SetFov(fov);
		SetAspect(width , height);
	}

	void SetView(const XMFLOAT3& eye , const XMFLOAT3& lookat , const XMFLOAT3& up)
	{
		SetEye(eye);
		SetLookat(lookat);
		SetUp(up);
	}

	const XMFLOAT4X4& GetProjectionMatrix()
	{
		return mProjection;
	}

	const XMFLOAT4X4& GetViewMatrix()
	{
		return mView;
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

	void JoinSpringArm(const CSpringArmComponent& partner)
	{
		mSpringArm = &partner;
	}
};