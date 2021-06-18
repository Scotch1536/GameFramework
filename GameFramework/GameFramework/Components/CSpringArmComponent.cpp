#include "../Actor/CActor.h"
#include "../Transform/CTransform.h"
#include "../Math/LCMath.h"

#include "CCameraComponent.h"
#include "CSpringArmComponent.h"

CSpringArmComponent::CSpringArmComponent(CActor& owner , const CTransform& targetTrans , CCameraComponent& useCamera , float time , EMovement move , int priority)
	:CComponent(owner , priority) ,
	mTargetTransform(targetTrans) ,
	mUseCamera(useCamera) ,
	mTimeToGoal(time) ,
	mLerpAlphaIncrement(1.0f / (60 * time))
{
	XMFLOAT3 targetLocation = mTargetTransform.Location;
	XMFLOAT3 cameraEye = useCamera.GetEye();

	mDistance.x = targetLocation.x - cameraEye.x;
	mDistance.y = targetLocation.y - cameraEye.y;
	mDistance.z = targetLocation.z - cameraEye.z;
}

void CSpringArmComponent::Update()
{
	if(mGoalCameraLocation == nullptr)
	{
		if(mMovement == EMovement::TARGET_SYNC)
		{
			XMFLOAT3 targetLocation = mTargetTransform.Location;
			targetLocation.x += mDistance.x;
			targetLocation.y += mDistance.y;
			targetLocation.z += mDistance.z;

			mGoalCameraLocation.reset(new XMFLOAT3(targetLocation));
		}
		else if(mMovement == EMovement::FOLLOW_BEHIND)
		{

		}
	}

	XMFLOAT3 cameraLocation = mUseCamera.GetEye();
	XMFLOAT3 goalLocation = *mGoalCameraLocation;
	LCMath::Lerp(cameraLocation.x,goalLocation.x,)
}