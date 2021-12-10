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
	XMFLOAT4X4 mProjection;		//プロジェクション行列

	XMFLOAT4X4 mCameraTransMatrixBase;		//カメラ座標変換行列のベース
	XMFLOAT4X4 mCameraTransMatrix;			//カメラ座標変換行列
	XMFLOAT4X4 mView;						//ビュー行列

	XMFLOAT3 mEye;				//カメラ位置(相対座標)
	XMFLOAT3 mLookAt;			//注視点
	XMFLOAT3 mUp;				//上向きベクトル

	float mNear;				//ニアクリップ
	float mFar;					//ファークリップ
	float mAspect;				//アスペクト比
	float mFov;					//視野角

	const CSpringArmComponent* mSpringArm = nullptr;		//スプリングアーム

	bool mShouldUpdateProjectionMatrix = true;		//プロジェクション行列を更新すべきか
	bool mShouldUpdateViewMatrix = true;			//ビュー行列を更新すべきか

	//プロジェクション行列作成
	void CreateProjectionMatrix();

	//ビュー行列作成
	void CreateViewMatrix();

	//更新
	void Update()override;

public:
	CCameraComponent(CActor& owner , int priority = 0):CComponent(owner , priority)
	{
		LCMath::IdentityMatrix(mProjection);
		LCMath::IdentityMatrix(mCameraTransMatrixBase);
		LCMath::IdentityMatrix(mCameraTransMatrix);
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

	void JoinSpringArm(const CSpringArmComponent& partner)
	{
		mSpringArm = &partner;
	}
};