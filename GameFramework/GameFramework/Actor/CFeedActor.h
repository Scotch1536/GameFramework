#pragma once
#include <functional>

#include "../Game/CApplication.h"
#include "../Level/CLevel.h"

#include "CActor.h"
#include "CDisplay2DActor.h"

class CFeedActor :public CActor
{
public:
	enum class EOption
	{
		FEEDOUT ,
		FEEDIN
	};

private:
	CDisplay2DActor* mFeedScreen;

	std::function<void()> mDoAfterFeedFunction;

	EOption mOption;

	float mAlpha;
	float mIncreaseAlpha;

public:
	CFeedActor(ILevel& partner , std::function<void()> func , EOption option , XMFLOAT3 color = { 1.0f,1.0f,1.0f } , float feedTime = 1.0f):CActor(partner) ,
		mDoAfterFeedFunction(func) , mOption(option) , mIncreaseAlpha(1.0f / (feedTime*60.0f))
	{
		float a = 1.0f / (feedTime*60.0f);
		if(mOption == EOption::FEEDOUT)mAlpha = 0.0f;
		else if(mOption == EOption::FEEDIN)	mAlpha = 1.0f;

		mFeedScreen = new CDisplay2DActor(mOwnerInterface , XMFLOAT4(color.x , color.y , color.z , mAlpha));
		mFeedScreen->Transform.Location.x = static_cast<float>(CApplication::CLIENT_WIDTH) / 2;
		mFeedScreen->Transform.Location.y = static_cast<float>(CApplication::CLIENT_HEIGHT) / 2;
		mFeedScreen->Transform.Scale.x = CApplication::CLIENT_WIDTH;
		mFeedScreen->Transform.Scale.y = CApplication::CLIENT_HEIGHT;
	}

	void Tick()override
	{
		bool isFeedEnd = false;

		if(mOption == EOption::FEEDOUT)mAlpha += mIncreaseAlpha;
		else if(mOption == EOption::FEEDIN)	mAlpha -= mIncreaseAlpha;

		if(mOption == EOption::FEEDOUT)
		{
			if(mAlpha >= 1.0f)
			{
				mAlpha = 1.0f;
				isFeedEnd = true;
			}
		}
		else if(mOption == EOption::FEEDIN)
		{
			if(mAlpha <= 0.0f)
			{
				mAlpha = 0.0f;
				isFeedEnd = true;
			}
		}

		XMFLOAT4 color = mFeedScreen->GetColor();
		color.w = mAlpha;
		mFeedScreen->SetColor(color);

		if(isFeedEnd)
		{
			if(mDoAfterFeedFunction != nullptr)mDoAfterFeedFunction();
			mOwnerInterface.DestroyActor(*this);
		}
	}
};