#include "CCameraComponent.h"
#include "CSpringArmComponent.h"

void CCameraComponent::CreateProjectionMatrix()
{
	ALIGN16 XMMATRIX projection;

	projection = XMMatrixPerspectiveFovLH(mFov , mAspect , mNear , mFar);

	XMStoreFloat4x4(&mProjection , projection);
}

void CCameraComponent::CreateViewMatrix()
{
	XMFLOAT3 eye;

	if(mSpringArm != nullptr)
	{
		eye = mEye;
	}
	else
	{
		XMFLOAT3 pLoc = mOwnerInterface.GetTransform().Location;
		eye = { pLoc.x + mEye.x , pLoc.y + mEye.y , pLoc.z + mEye.z };
	}

	XMFLOAT3 vecX , vecY , vecZ;

	LCMath::CalcFloat3FromStartToGoal(eye , mLookAt , vecZ);
	LCMath::CalcFloat3Normalize(vecZ , vecZ);

	LCMath::CalcFloat3Cross(mUp , vecZ , vecX);
	LCMath::CalcFloat3Normalize(vecX , vecX);

	LCMath::CalcFloat3Cross(vecZ , vecX , vecY);
	LCMath::CalcFloat3Normalize(vecY , vecY);

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

	LCMath::InverseMatrix(mCameraTransMatrixBase , mView);
}

void CCameraComponent::Update()
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