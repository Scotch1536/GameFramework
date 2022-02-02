//!
//! @file
//! @brief カメラコンポーネントのソースファイル
//!

#include "CCameraComponent.h"
#include "CSpringArmComponent.h"

void CCameraComponent::Update()
{
	if(mShouldUpdateProjectionMatrix)
	{
		mShouldUpdateProjectionMatrix = false;

		UpdateProjectionMatrix();		//プロジェクション行列更新
	}

	if(mShouldUpdateViewMatrix)
	{
		mShouldUpdateViewMatrix = false;

		UpdateViewMatrix();			//ビュー行列更新
	}
}

void CCameraComponent::UpdateViewMatrix()
{
	XMFLOAT3 eye;

	//スプリングアームがあるか
	if(mSpringArm != nullptr)
	{
		eye = mEye;
	}
	else
	{
		//カメラ位置をワールド座標系に変換する
		XMFLOAT3 pLoc = mOwnerInterface.GetTransform().Location;
		eye = { pLoc.x + mEye.x , pLoc.y + mEye.y , pLoc.z + mEye.z };
	}

	XMFLOAT3 vecX , vecY , vecZ;

	//カメラ位置から注視点に向かうベクトルをZ軸とする
	LCMath::CalcFloat3FromStartToEnd(eye , mLookAt , vecZ);
	LCMath::CalcFloat3Normalize(vecZ , vecZ);

	//上向きベクトルとZ軸の外積の結果をX軸とする
	LCMath::CalcFloat3Cross(mUp , vecZ , vecX);
	LCMath::CalcFloat3Normalize(vecX , vecX);

	//Z軸とX軸の外積の結果をY軸とする
	LCMath::CalcFloat3Cross(vecZ , vecX , vecY);
	LCMath::CalcFloat3Normalize(vecY , vecY);

	//カメラ座標変換行列のベースの初期化
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

	//カメラ座標変換行列の逆行列をビュー行列とする
	LCMath::InverseMatrix(mCameraTransMatrix , mView);
}

void CCameraComponent::UpdateProjectionMatrix()
{
	ALIGN16 XMMATRIX projection;

	//プロジェクション行列作成
	projection = XMMatrixPerspectiveFovLH(mFov , mAspect , mNear , mFar);

	//型変換
	XMStoreFloat4x4(&mProjection , projection);
}
