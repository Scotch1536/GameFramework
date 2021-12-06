#include "../Managers/CGameManager.h"

#include "C2DAnimationComponent.h"

C2DAnimationComponent::C2DAnimationComponent(CActor& owner , int divWidth , int divHeight)
	:CSquareDivisionComponent(owner , divWidth , divHeight)
{}

void C2DAnimationComponent::AddAnimData(XMFLOAT2* changeUV1 , XMFLOAT2* changeUV2 , XMFLOAT2* changeUV3 , XMFLOAT2* changeUV4 , std::function<void()> functionWhenChangingUV , std::string alias)
{
	mAnimData.emplace_back();
	mAnimDataIndexAlias.emplace_back();
	mAnimData.back().AnimName = "NONE";
	mAnimData.back().ChangeTargetUV1 = changeUV1;
	mAnimData.back().ChangeTargetUV2 = changeUV2;
	mAnimData.back().ChangeTargetUV3 = changeUV3;
	mAnimData.back().ChangeTargetUV4 = changeUV4;
	mAnimData.back().FunctionWhenChangingUV = functionWhenChangingUV;

	if(alias != "NONE")
	{
		mAnimDataIndexAlias.back() = alias;
	}
}

void C2DAnimationComponent::Update()
{
	for(auto& anim : mAnimData)
	{
		if(mAnimInfo[anim.AnimName].second && !anim.IsPlay)anim.IsPlay = true;
		if(!anim.IsPlay)continue;

		anim.TimeCounter += CGameManager::GetInstance().GetDeltaTime();

		int changeNum = anim.TimeCounter / anim.AnimFrameTime;

		if(changeNum >= 1)
		{
			anim.AnimCounter += changeNum;
			anim.TimeCounter -= anim.AnimFrameTime * changeNum;

			if(anim.AnimCounter >= anim.AnimFrameMax)
			{
				if(mAnimInfo[anim.AnimName].second)
				{
					anim.AnimCounter = anim.AnimCounter % anim.AnimFrameMax;
				}
				else
				{
					anim.AnimCounter = anim.AnimFrameMax - 1;
					anim.IsPlay = false;
				}
			}

			int index = anim.AnimStartIndex + anim.AnimCounter;

			*anim.ChangeTargetUV1 = mUVDivisionData.at(index).at(0);
			*anim.ChangeTargetUV2 = mUVDivisionData.at(index).at(1);
			*anim.ChangeTargetUV3 = mUVDivisionData.at(index).at(2);
			*anim.ChangeTargetUV4 = mUVDivisionData.at(index).at(3);

			anim.FunctionWhenChangingUV();
		}
	}
}