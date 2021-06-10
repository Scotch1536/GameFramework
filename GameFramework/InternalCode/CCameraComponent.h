#include <DirectXMath.h>

#include "Memory.h"
#include "CComponent.h"
#include "DX11Settransform.h"

class CCameraComponent :public CComponent
{
private:
	XMFLOAT4X4 mProjection;		//プロジェクション行列

	XMFLOAT4X4 mView;			//ビュー行列

	XMFLOAT3 mEye;				//カメラ位置
	XMFLOAT3 mLookat;			//注視点
	XMFLOAT3 mUp;				//上向きベクトル

	float mNear;				//ニアクリップ
	float mFar;					//ファークリップ
	float mAspect;				//アスペクト比
	float mFov;					//視野角

	bool mShouldUpdateProjectionMatrix = true;		//プロジェクション行列を更新すべきか
	bool mShouldUpdateViewMatrix = true;			//ビュー行列を更新すべきか

	//プロジェクション行列作成
	void CreateProjectionMatrix()
	{
		ALIGN16 XMMATRIX projection;

		projection = XMMatrixPerspectiveFovLH(mFov , mAspect , mNear , mFar);

		XMStoreFloat4x4(&mProjection , projection);
	}

	//ビュー行列作成
	void CreateViewMatrix()
	{
		ALIGN16 XMVECTOR Eye = XMVectorSet(mEye.x , mEye.y , mEye.z , 0.0f);
		ALIGN16 XMVECTOR At = XMVectorSet(mLookat.x , mLookat.y , mLookat.z , 0.0f);
		ALIGN16 XMVECTOR Up = XMVectorSet(mUp.x , mUp.y , mUp.z , 0.0f);

		ALIGN16 XMMATRIX camera;
		camera = XMMatrixLookAtLH(Eye , At , Up);

		XMStoreFloat4x4(&mView , camera);
	}

public:
	CCameraComponent(IActor& owner , int priority = 80):CComponent(owner , priority)
	{
		mAttribute = CComponent::EAttribute::CAMERA;
	}

	//更新
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

	const XMFLOAT3& GetLookat() const
	{
		return mLookat;
	}

	const XMFLOAT3& GetUp() const
	{
		return mUp;
	}

	float GetFov() const
	{
		return mFov;
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

		mLookat = lookat;
	}

	void SetUp(const XMFLOAT3& up)
	{
		if(!mShouldUpdateViewMatrix)mShouldUpdateViewMatrix = true;

		mUp = up;
	}
};