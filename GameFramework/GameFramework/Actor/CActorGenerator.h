#pragma once
#include <random>
#include <functional>

#include "../Level/CLevel.h"

#include "CActor.h"

class CActorGenerator :public CActor
{
private:
	std::function<CActor*()> mInstantiationEvent;		//�C���X�^���X���C�x���g

	std::random_device mRandomSeed;			//�����f�o�C�X
	std::mt19937 mRandomEngine;				//�����A���S���Y��

	//����������
	std::uniform_real_distribution<float> mRandomGeneratorX;
	std::uniform_real_distribution<float> mRandomGeneratorY;
	std::uniform_real_distribution<float> mRandomGeneratorZ;

	int mGenerationLimit;				//�������E�l
	int mGenerationCounter = 0;			//�����J�E���^�[

	float mGenerationGauge = 0.0f;				//�����Q�[�W
	float mIncreasedValueOfGenerationGauge;		//�����Q�[�W�̑����l�i���t���[���j

public:
	CActorGenerator(ILevel& partner , std::function<CActor*()> instantiationEvent , XMFLOAT3 minRange , XMFLOAT3 maxRange , float generationPerSecond , int generationLimit = 1000):CActor(partner) ,
		mInstantiationEvent(instantiationEvent) ,
		mRandomEngine(mRandomSeed()) , mRandomGeneratorX(minRange.x , maxRange.x) ,
		mRandomGeneratorY(minRange.y , maxRange.y) , mRandomGeneratorZ(minRange.z , maxRange.z) ,
		mGenerationLimit(generationLimit) , mIncreasedValueOfGenerationGauge(generationPerSecond / 60.0f)
	{}

	void Tick()override
	{
		mGenerationGauge += mIncreasedValueOfGenerationGauge;
		int numGeneration = mGenerationGauge / 1;

		if(numGeneration >= 1)
		{
			mGenerationGauge -= numGeneration;

			auto generationActor = [& , numGeneration]
			{
				for(int i = 0; i < numGeneration; ++i)
				{
					if(mGenerationLimit <= mGenerationCounter)break;

					CActor* actor = mInstantiationEvent();

					actor->Transform.Location.x = mRandomGeneratorX(mRandomEngine);
					actor->Transform.Location.y = mRandomGeneratorY(mRandomEngine);
					actor->Transform.Location.z = mRandomGeneratorZ(mRandomEngine);

					mGenerationCounter++;
				}
			};
			mOwnerInterface.AddDoBeforeUpdateFunction(generationActor);
		}
	}

	const int& GetGenerationCounter()const
	{
		return mGenerationCounter;
	}
};