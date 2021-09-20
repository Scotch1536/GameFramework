#pragma once
#include <random>
#include <functional>

#include "../Level/CLevel.h"

#include "CActor.h"

class CActorGenerator :public CActor
{
private:
	std::function<CActor*()> mInstantiationEvent;

	std::random_device mRandomSeed;
	std::mt19937 mRandomEngine;
	std::uniform_real_distribution<float> mRandomGeneratorX;
	std::uniform_real_distribution<float> mRandomGeneratorY;
	std::uniform_real_distribution<float> mRandomGeneratorZ;

	int mGenerationLimit;
	int mGenerationCounter = 0;

	float mGenerationGauge = 0.0f;
	float mGenerationGaugePerFrame;

public:
	CActorGenerator(ILevel& partner , std::function<CActor*()> instantiationEvent , XMFLOAT3 minRange , XMFLOAT3 maxRange , float generationPerSecond , int generationLimit = 1000):CActor(partner) ,
		mInstantiationEvent(instantiationEvent) ,
		mRandomEngine(mRandomSeed()) , mRandomGeneratorX(minRange.x , maxRange.x) ,
		mRandomGeneratorY(minRange.y , maxRange.y) , mRandomGeneratorZ(minRange.z , maxRange.z) ,
		mGenerationLimit(generationLimit) , mGenerationGaugePerFrame(generationPerSecond / 60.0f)
	{}

	void Tick()override
	{
		mGenerationGauge += mGenerationGaugePerFrame;
		int numGeneration = mGenerationGauge / 1;

		if(numGeneration >= 1)
		{
			mGenerationGauge -= numGeneration;
			mGenerationCounter += numGeneration;

			if(mGenerationLimit >= mGenerationCounter)
			{
				auto generationActor = [& , numGeneration]
				{
					for(int i = 0; i < numGeneration; ++i)
					{
						CActor* actor = mInstantiationEvent();

						actor->Transform.Location.x = mRandomGeneratorX(mRandomEngine);
						actor->Transform.Location.y = mRandomGeneratorY(mRandomEngine);
						actor->Transform.Location.z = mRandomGeneratorZ(mRandomEngine);
					}
				};
				mOwnerInterface.AddDoBeforeUpdateFunction(generationActor);
			}
		}
	}

	const int& GetGenerationCounter()const
	{
		return mGenerationCounter;
	}

	void SetGenerationCounter(int count)
	{
		mGenerationCounter = count;
	}
};