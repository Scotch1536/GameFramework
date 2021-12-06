#include "../Managers/CGameManager.h"

#include "C2DAnimationComponent.h"

C2DAnimationComponent::C2DAnimationComponent(CActor& owner , int divWidth , int divHeight , float oneLoopTime , bool isLoop ,
	XMFLOAT2& changeTargetUV1 , XMFLOAT2& changeTargetUV2 , XMFLOAT2& changeTargetUV3 , XMFLOAT2& changeTargetUV4)
	:CSquareDivisionComponent(owner , divWidth , divHeight) , mIsLoop(isLoop) ,
	mChangeTargetUV1(changeTargetUV1) , mChangeTargetUV2(changeTargetUV2) ,
	mChangeTargetUV3(changeTargetUV4) , mChangeTargetUV4(changeTargetUV4)
{
	mAnimFrameMax = divWidth * divHeight;
	mAnimFrameTime = oneLoopTime / mAnimFrameMax;

	mChangeTargetUV1 = mUVDivisionData.at(0).at(0);
	mChangeTargetUV2 = mUVDivisionData.at(0).at(1);
	mChangeTargetUV3 = mUVDivisionData.at(0).at(2);
	mChangeTargetUV4 = mUVDivisionData.at(0).at(3);
}

void C2DAnimationComponent::Update()
{
	if(mIsLoop && !mShouldUpdate)mShouldUpdate = true;
	if(!mShouldUpdate)return;

	mTimeCounter += CGameManager::GetInstance().GetDeltaTime();

	int changeNum = mTimeCounter / mAnimFrameTime;

	if(changeNum >= 1)
	{
		mAnimCounter += changeNum;
		mTimeCounter -= mAnimFrameTime * changeNum;

		if(mAnimCounter >= mAnimFrameMax)
		{
			if(mIsLoop)
			{
				mAnimCounter = mAnimCounter % mAnimFrameMax;
			}
			else
			{
				mAnimCounter = mAnimFrameMax - 1;
				mShouldUpdate = false;
			}
		}

		mChangeTargetUV1 = mUVDivisionData.at(mAnimCounter).at(0);
		mChangeTargetUV2 = mUVDivisionData.at(mAnimCounter).at(1);
		mChangeTargetUV3 = mUVDivisionData.at(mAnimCounter).at(2);
		mChangeTargetUV4 = mUVDivisionData.at(mAnimCounter).at(3);
	}
}