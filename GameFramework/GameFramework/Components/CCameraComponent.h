#pragma once
#include <DirectXMath.h>

#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/Memory.h"
#include "../Actor/CActor.h"
#include "../Library/LCMath.h"

#include "CComponent.h"

//!
//! @file
//! @brief カメラコンポーネントのヘッダーファイル
//!

class CSpringArmComponent;

//! @brief カメラコンポーネントクラス
class CCameraComponent :public CComponent
{
private:
	XMFLOAT4X4 mView;						//!< ビュー行列
	XMFLOAT4X4 mCameraTransMatrixBase;		//!< カメラ座標変換行列のベース
	XMFLOAT4X4 mCameraTransMatrix;			//!< カメラ座標変換行列

	XMFLOAT4X4 mProjection;					//!< プロジェクション行列

	//! @brief カメラ位置
	//! スプリングアームと繋がっている場合はターゲットのトランスフォームからの相対座標
	//! スプリングアームと繋がっていない場合は自身のコンポーネント所有者のアクターのトランスフォームからの相対座標
	XMFLOAT3 mEye;
	XMFLOAT3 mLookAt;			//!< 注視点
	XMFLOAT3 mUp;				//!< 上向きベクトル

	float mNear;				//!< ニアクリップ
	float mFar;					//!< ファークリップ
	float mAspect;				//!< アスペクト比
	float mFov;					//!< 視野角

	const CSpringArmComponent* mSpringArm = nullptr;		//!< スプリングアーム

	bool mShouldUpdateProjectionMatrix = true;				//!< プロジェクション行列を更新すべきか
	bool mShouldUpdateViewMatrix = true;					//!< ビュー行列を更新すべきか

	//! @brief 更新
	void Update()override;

	//! @brief ビュー行列更新
	void UpdateViewMatrix();

	//! @brief プロジェクション行列更新
	void UpdateProjectionMatrix();

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントの所有者
	//! @param[in] priority 優先度
	//!
	CCameraComponent(CActor& owner , int priority = 0):CComponent(owner , priority)
	{
		//行列の初期化
		LCMath::IdentityMatrix(mProjection);
		LCMath::IdentityMatrix(mCameraTransMatrixBase);
		LCMath::IdentityMatrix(mCameraTransMatrix);
		LCMath::IdentityMatrix(mView);
	}

	//!
	//! @brief ビュー情報のセット
	//! @param[in] eye カメラの（目の）位置
	//! @param[in] lookat 注視点
	//! @param[in] up 上向きベクトル
	//!
	void SetView(const XMFLOAT3& eye , const XMFLOAT3& lookat , const XMFLOAT3& up)
	{
		SetEye(eye);
		SetLookat(lookat);
		SetUp(up);
	}

	//!
	//! @brief プロジェクション情報のセット
	//! @param[in] nearclip 二アークリップ
	//! @param[in] farclip ファークリップ
	//! @param[in] fov 視野角
	//! @param[in] width 横のウィンドウサイズ
	//! @param[in] height 縦のウィンドウサイズ
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

		//カメラ座標変換行列の逆行列をビュー行列とする
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

	//! @brief スプリングアームを繋げる
	void JoinSpringArm(const CSpringArmComponent& partner)
	{
		mSpringArm = &partner;
	}
};