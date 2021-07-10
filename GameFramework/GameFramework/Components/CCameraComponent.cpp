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
	if(mSpringArm != nullptr)
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