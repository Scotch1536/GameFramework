#include <DirectXMath.h>

#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/Memory.h"
#include "../Actor/CActor.h"

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

	bool mShouldUpdateProjectionMatrix = true;		//�v���W�F�N�V�����s����X�V���ׂ���
	bool mShouldUpdateViewMatrix = true;			//�r���[�s����X�V���ׂ���
	bool mIsJoinSpringArm = false;					//�X�v�����O�A�[�����q�����Ă��邩

	//�v���W�F�N�V�����s��쐬
	void CreateProjectionMatrix()
	{
		ALIGN16 XMMATRIX projection;

		projection = XMMatrixPerspectiveFovLH(mFov , mAspect , mNear , mFar);

		XMStoreFloat4x4(&mProjection , projection);
	}

	//�r���[�s��쐬
	void CreateViewMatrix()
	{
		if(mIsJoinSpringArm)
		{
			ALIGN16 XMVECTOR Eye = XMVectorSet(mEye.x , mEye.y , mEye.z , 0.0f);
			ALIGN16 XMVECTOR At = XMVectorSet(mLookAt.x , mLookAt.y , mLookAt.z , 0.0f);
			ALIGN16 XMVECTOR Up = XMVectorSet(mUp.x , mUp.y , mUp.z , 0.0f);

			ALIGN16 XMMATRIX camera;
			camera = XMMatrixLookAtLH(Eye , At , Up);

			XMStoreFloat4x4(&mView , camera);
		}
		else
		{
			XMFLOAT3 pLoc = mOwnerInterface.GetTransform().Location;

			ALIGN16 XMVECTOR Eye = XMVectorSet(pLoc.x + mEye.x , pLoc.y + mEye.y , pLoc.z + mEye.z , 0.0f);
			ALIGN16 XMVECTOR At = XMVectorSet(mLookAt.x , mLookAt.y , mLookAt.z , 0.0f);
			ALIGN16 XMVECTOR Up = XMVectorSet(mUp.x , mUp.y , mUp.z , 0.0f);

			ALIGN16 XMMATRIX camera;
			camera = XMMatrixLookAtLH(Eye , At , Up);

			XMStoreFloat4x4(&mView , camera);
		}
	}

public:
	CCameraComponent(CActor& owner , int priority = 80):CComponent(owner , priority) {}

	//�X�V
	void Update()override
	{
		if(mShouldUpdateProjectionMatrix)
		{
			mShouldUpdateProjectionMatrix = false;

			CreateProjectionMatrix();
		}

		if(mShouldUpdateViewMatrix)
		{
			mShouldUpdateViewMatrix = false;

			CreateViewMatrix();
		}
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
		mIsJoinSpringArm = true;
	}
};