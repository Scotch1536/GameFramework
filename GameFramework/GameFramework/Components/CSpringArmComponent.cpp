#include "../Actor/CActor.h"
#include "../Transform/CTransform.h"
#include "../ExternalCode/dx11mathutil.h"
#include "../Math/LCMath.h"

#include "CCameraComponent.h"
#include "CSpringArmComponent.h"

CSpringArmComponent::CSpringArmComponent(CActor& owner , const CTransform& parentTrans , CCameraComponent& useCamera , ESyncMode syncMode , int priority)
	:CComponent(owner , priority) ,
	mSyncMode(syncMode) ,
	mParentTransform(parentTrans) ,
	mUseCamera(useCamera)
{
	//カメラコンポーネントにスプリングアームを繋げたことを通知
	mUseCamera.JoinSpringArm(*this);

	DX11MtxIdentity(mLocalMatrix);
}

void CSpringArmComponent::UpdateLocalMatrix()
{
	ResetPalam();

	XMFLOAT3 eye = mUseCamera.GetEye();
	XMFLOAT3 lockAt = mUseCamera.GetLookat();
	XMFLOAT3 up = mUseCamera.GetUp();

	mLocalMatrix._11 = eye.x;
	mLocalMatrix._12 = eye.y;
	mLocalMatrix._13 = eye.z;
	mLocalMatrix._14 = 1;

	mLocalMatrix._21 = up.x - eye.x;
	mLocalMatrix._22 = up.y - eye.y;
	mLocalMatrix._23 = up.z - eye.z;
	mLocalMatrix._24 = 0;

	mLocalMatrix._31 = lockAt.x;
	mLocalMatrix._32 = lockAt.y;
	mLocalMatrix._33 = lockAt.z;
	mLocalMatrix._34 = 1;

	mLocalMatrix._41 = 0;
	mLocalMatrix._42 = 0;
	mLocalMatrix._43 = 0;
	mLocalMatrix._44 = 0;
}

void CSpringArmComponent::IncreaseAlpha()
{
	mAlpha += mIncrementAlpha;

	if(mAlpha >= 1.0f)
	{
		mAlpha = 1.0f;
	}
}

void CSpringArmComponent::Update()
{
	if(mUseCamera.GetShouldUpdateViewMatrix())UpdateLocalMatrix();

	if(mSyncMode == ESyncMode::ALL_SYNC)
	{
		XMFLOAT4X4 cameraWorld;

		DX11MtxMultiply(cameraWorld , mLocalMatrix , mParentTransform.GetWorldMatrixResult());

		if(mGoalWorldMatrix != nullptr)
		{
			if(!LCMath::CompareMatrix(*mGoalWorldMatrix , cameraWorld))
			{
				mGoalWorldMatrix.reset(new XMFLOAT4X4(cameraWorld));

				mGoalEye.reset(new XMFLOAT3(mGoalWorldMatrix->_11 , mGoalWorldMatrix->_12 , mGoalWorldMatrix->_13));
				mGoalLockAt.reset(new XMFLOAT3(mGoalWorldMatrix->_31 , mGoalWorldMatrix->_32 , mGoalWorldMatrix->_33));
				mGoalUp.reset(new XMFLOAT3(mGoalWorldMatrix->_21 , mGoalWorldMatrix->_22 , mGoalWorldMatrix->_23));

				mAlpha = 0.0f;
			}
		}
		else
		{
			mGoalWorldMatrix.reset(new XMFLOAT4X4(cameraWorld));

			mGoalEye.reset(new XMFLOAT3(mGoalWorldMatrix->_11 , mGoalWorldMatrix->_12 , mGoalWorldMatrix->_13));
			mGoalLockAt.reset(new XMFLOAT3(mGoalWorldMatrix->_31 , mGoalWorldMatrix->_32 , mGoalWorldMatrix->_33));
			mGoalUp.reset(new XMFLOAT3(mGoalWorldMatrix->_21 , mGoalWorldMatrix->_22 , mGoalWorldMatrix->_23));

			mAlpha = 1.0f;
		}

		IncreaseAlpha();

		mUseCamera.SetEye(LCMath::Lerp(mUseCamera.GetEye() , *mGoalEye , mAlpha));
		mUseCamera.SetLookat(LCMath::Lerp(mUseCamera.GetLookat() , *mGoalLockAt , mAlpha));
		mUseCamera.SetUp(LCMath::Lerp(mUseCamera.GetUp() , *mGoalUp , mAlpha));
	}
	else if(mSyncMode == ESyncMode::LOCATION_ONLY_SYNC)
	{
		if(mGoalEye != nullptr)
		{
			if(!LCMath::CompareFloat3(*mGoalEye , mParentTransform.Location))
			{
				mGoalEye.reset(new XMFLOAT3(mParentTransform.Location));

				mGoalEye->x += mLocalMatrix._11;
				mGoalEye->y += mLocalMatrix._12;
				mGoalEye->z += mLocalMatrix._13;

				mAlpha = 0.0f;
			}
		}
		else
		{
			mGoalEye.reset(new XMFLOAT3(mParentTransform.Location));

			mGoalEye->x += mLocalMatrix._11;
			mGoalEye->y += mLocalMatrix._12;
			mGoalEye->z += mLocalMatrix._13;

			mAlpha = 1.0f;
		}

		IncreaseAlpha();

		LCMath::Lerp(mUseCamera.GetEye() , *mGoalEye , mAlpha);

		mUseCamera.SetEye(LCMath::Lerp(mUseCamera.GetEye() , *mGoalEye , mAlpha));
		mUseCamera.SetLookat({ mParentTransform.Location.x,mParentTransform.Location.y,mParentTransform.Location.z });
	}
}