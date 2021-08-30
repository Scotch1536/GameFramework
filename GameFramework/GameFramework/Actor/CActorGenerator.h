#pragma once
#include <random>
#include <functional>

#include "../Managers/CGameManager.h"
#include "CActor.h"

class CActorGenerator :public CActor
{
private:
	std::function<CActor*()> mInstantiationEvent;

	std::random_device mRandomSeed;
	std::mt19937 mRandomEngine;
	std::uniform_real_distribution<> mRandomGeneratorX;
	std::uniform_real_distribution<> mRandomGeneratorY;
	std::uniform_real_distribution<> mRandomGeneratorZ;

	float mDeltaTimeCounter = 0.0f;
	float mGenerationPerFrame;

public:
	CActorGenerator(ILevel& partner , std::function<CActor*()> instantiationEvent , XMFLOAT3 minRange , XMFLOAT3 maxRange , float generationPerSecond):CActor(partner) ,
		mInstantiationEvent(instantiationEvent) ,
		mRandomEngine(mRandomSeed()) , mRandomGeneratorX(minRange.x , maxRange.x) ,
		mRandomGeneratorY(minRange.y , maxRange.y) , mRandomGeneratorZ(minRange.z , maxRange.z) ,
		mGenerationPerFrame(generationPerSecond / 60.0f)
	{}

	void Tick()override
	{
		mDeltaTimeCounter += CGameManager::GetInstance().GetDeltaTime();
		int numGeneration = mDeltaTimeCounter / mGenerationPerFrame;

		if(numGeneration >= 1)
		{
			mDeltaTimeCounter -= mGenerationPerFrame * numGeneration;

			auto generationActor = [&]
			{
				for(int i = 0; i < numGeneration; ++i)
				{
					CActor* actor = mInstantiationEvent();

					actor->Transform.Location.x = mRandomGeneratorX(mRandomEngine);
					actor->Transform.Location.y = mRandomGeneratorY(mRandomEngine);
					actor->Transform.Location.z = mRandomGeneratorZ(mRandomEngine);
				}
			};
			mOwnerInterface.AddDoAfterTickFunction(generationActor);
		}
	}
};