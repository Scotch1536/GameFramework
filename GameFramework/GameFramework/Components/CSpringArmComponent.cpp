#include "../Actor/CActor.h"
#include "../Transform/CTransform.h"
#include "../Library/LCMath.h"

#include "CCameraComponent.h"
#include "CSpringArmComponent.h"

CSpringArmComponent::CSpringArmComponent(CActor& owner , const CTransform& parentTrans , CCameraComponent& useCamera , ESyncMode syncMode , int priority)
	:CComponent(owner , priority) ,
	mSyncMode(syncMode) ,
	mParentTransform(parentTrans) ,
	mUseCamera(useCamera) ,
	mInitEye(useCamera.GetEye()) ,
	mInitLockAt(useCamera.GetLookAt()) ,
	mInitUp(useCamera.GetUp())
{
	//カメラコンポーネントにスプリングアームを繋げたことを通知
	mUseCamera.JoinSpringArm(*this);

	LCMath::IdentityMatrix(mLocalMatrix);
}

void CSpringArmComponent::UpdateLocalMatrix()
{
	ResetGoal();

	XMFLOAT3 eye = mUseCamera.GetEye();
	XMFLOAT3 lockAt = mUseCamera.GetLookAt();
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

void CSpringArmComponent::ResetGoal()
{
	mResultWorldMatrix.reset();
	mResultEye.reset();
	mResultLockAt.reset();
	mResultUp.reset();
}

void CSpringArmComponent::Update()
{
	if(mUseCamera.GetShouldUpdateViewMatrix())UpdateLocalMatrix();

	if(mSyncMode == ESyncMode::ALL_SYNC)
	{
		XMFLOAT4X4 cameraWorld;

		LCMath::CalcMatrixMultply(mLocalMatrix , mParentTransform.GetWorldMatrixResult() , cameraWorld);

		if(mResultWorldMatrix != nullptr)
		{
			if(!LCMath::CompareMatrix(*mResultWorldMatrix , cameraWorld))
			{
				mResultWorldMatrix.reset(new XMFLOAT4X4(cameraWorld));

				mResultEye.reset(new XMFLOAT3(mResultWorldMatrix->_11 , mResultWorldMatrix->_12 , mResultWorldMatrix->_13));
				mResultLockAt.reset(new XMFLOAT3(mResultWorldMatrix->_31 , mResultWorldMatrix->_32 , mResultWorldMatrix->_33));
				mResultUp.reset(new XMFLOAT3(mResultWorldMatrix->_21 , mResultWorldMatrix->_22 , mResultWorldMatrix->_23));

				mAlpha = 0.0f;
			}
		}
		else
		{
			mResultWorldMatrix.reset(new XMFLOAT4X4(cameraWorld));

			mResultEye.reset(new XMFLOAT3(mResultWorldMatrix->_11 , mResultWorldMatrix->_12 , mResultWorldMatrix->_13));
			mResultLockAt.reset(new XMFLOAT3(mResultWorldMatrix->_31 , mResultWorldMatrix->_32 , mResultWorldMatrix->_33));
			mResultUp.reset(new XMFLOAT3(mResultWorldMatrix->_21 , mResultWorldMatrix->_22 , mResultWorldMatrix->_23));

			mAlpha = 1.0f;
		}

		IncreaseAlpha();

		XMFLOAT3 eye , lookAt , up;

		mUseCamera.SetEye(LCMath::Lerp(mUseCamera.GetEye() , *mResultEye , mAlpha , eye));
		mUseCamera.SetLookat(LCMath::Lerp(mUseCamera.GetLookAt() , *mResultLockAt , mAlpha , lookAt));
		mUseCamera.SetUp(LCMath::Lerp(mUseCamera.GetUp() , *mResultUp , mAlpha , up));
	}
	else if(mSyncMode == ESyncMode::LOCATION_ONLY_SYNC)
	{
		XMFLOAT3 compareLocation = mParentTransform.Location;

		compareLocation.x += mLocalMatrix._11;
		compareLocation.y += mLocalMatrix._12;
		compareLocation.z += mLocalMatrix._13;

		if(mResultEye != nullptr)
		{
			if(!LCMath::CompareFloat3(*mResultEye , compareLocation))
			{
				mResultEye.reset(new XMFLOAT3(compareLocation));

				mAlpha = 0.0f;
			}
		}
		else
		{
			mResultEye.reset(new XMFLOAT3(compareLocation));

			mAlpha = 1.0f;
		}

		IncreaseAlpha();

		XMFLOAT3 eye;

		mUseCamera.SetEye(LCMath::Lerp(mUseCamera.GetEye() , *mResultEye , mAlpha , eye));
		mUseCamera.SetLookat(mParentTransform.Location);
	}
}