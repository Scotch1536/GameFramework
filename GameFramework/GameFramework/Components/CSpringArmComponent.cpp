#include "../Actor/CActor.h"
#include "../Transform/CTransform.h"
#include "../Library/LCMath.h"

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
	XMFLOAT4X4 idealMatrix;

	if(mSyncMode == ESyncMode::ALL_SYNC)
	{
		LCMath::CalcMatrixMultply(mUseCamera.GetCameraTransMatrixBase() , mParentTransform.GetWorldMatrixResult() , idealMatrix);
	}
	else if(mSyncMode == ESyncMode::LOCATION_ONLY_SYNC)
	{
		idealMatrix = mUseCamera.GetCameraTransMatrixBase();
		idealMatrix._41 += mParentTransform.Location.x;
		idealMatrix._42 += mParentTransform.Location.y;
		idealMatrix._43 += mParentTransform.Location.z;
	}

	if(mIdealMatrix != nullptr)
	{
		if(!LCMath::CompareMatrix(*mIdealMatrix , idealMatrix) && mAlpha != 0.0f)
		{
			mIdealMatrix.reset(new XMFLOAT4X4(idealMatrix));

			mAlpha = 0.0f;

			mUseCamera.SetCameraTransMatrix(LCMath::Lerp(mUseCamera.GetCameraTransMatrix() , *mIdealMatrix , mAlpha));

			return;
		}
	}
	else
	{
		mIdealMatrix.reset(new XMFLOAT4X4(idealMatrix));

		mUseCamera.SetCameraTransMatrix(LCMath::Lerp(mUseCamera.GetCameraTransMatrix() , *mIdealMatrix , 1.0f));

		return;
	}

	IncreaseAlpha();

	mUseCamera.SetCameraTransMatrix(LCMath::Lerp(mUseCamera.GetCameraTransMatrix() , *mIdealMatrix , mAlpha));
}