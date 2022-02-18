//!
//! @file
//! @brief �A�N�^�[�W�F�l���[�^�[�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <random>
#include <functional>

#include "../Level/CLevel.h"

#include "CActor.h"

//! @brief �A�N�^�[�W�F�l���[�^�[�N���X
class CActorGenerator :public CActor
{
private:
	std::function<CActor*()> mInstantiationEvent;					//!< �C���X�^���X���C�x���g

	std::random_device mRandomSeed;									//!< �����f�o�C�X
	std::mt19937 mRandomEngine;										//!< �����A���S���Y��

	std::uniform_real_distribution<float> mRandomGeneratorX;		//!< ����������X
	std::uniform_real_distribution<float> mRandomGeneratorY;		//!< ����������Y
	std::uniform_real_distribution<float> mRandomGeneratorZ;		//!< ����������Z

	int mGenerationLimit;											//!< �������E�l�i�����j
	int mGenerationCounter = 0;										//!< �����J�E���^�[

	float mGenerationGauge = 0.0f;									//!< �����Q�[�W
	float mIncreasedValueOfGenerationGauge;							//!< �����Q�[�W�̑����l�i���t���[���j

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] partner ���̃A�N�^�[�����L���郌�x��
	//! @param[in] instantiationEvent �C���X�^���X���C�x���g
	//! @param[in] minRange �����͈͂̍ŏ��l
	//! @param[in] maxRange �����͈͂̍ő�l
	//! @param[in] generationPerSecond 1�b������̐�����
	//! @param[in] generationLimit �������E�l�i�����j
	//!
	CActorGenerator(ILevel& partner , std::function<CActor*()> instantiationEvent , XMFLOAT3 minRange , XMFLOAT3 maxRange , float generationPerSecond , int generationLimit = 1000)
		:CActor(partner) , mInstantiationEvent(instantiationEvent) ,
		mRandomEngine(mRandomSeed()) , mRandomGeneratorX(minRange.x , maxRange.x) ,
		mRandomGeneratorY(minRange.y , maxRange.y) , mRandomGeneratorZ(minRange.z , maxRange.z) ,
		mGenerationLimit(generationLimit) , mIncreasedValueOfGenerationGauge(generationPerSecond / 60.0f)
	{}

	//! @brief �e�B�b�N�i���t���[���s���ǉ������j
	void Tick()override
	{
		//�Q�[�W�̍X�V
		mGenerationGauge += mIncreasedValueOfGenerationGauge;

		//�������Z�o
		int numGeneration = mGenerationGauge / 1;

		//��������1�ȏ�Ȃ�
		if(numGeneration >= 1)
		{
			//�Q�[�W�̍X�V
			mGenerationGauge -= numGeneration;

			//�A�N�^�[�����̊֐��I�u�W�F�N�g�쐬
			auto generationActor = [& , numGeneration]
			{
				for(int i = 0; i < numGeneration; ++i)
				{
					if(mGenerationLimit <= mGenerationCounter)break;

					//�C���X�^���X��
					CActor* actor = mInstantiationEvent();

					//���P�[�V�����̎Z�o
					actor->Transform.Location.x = mRandomGeneratorX(mRandomEngine);
					actor->Transform.Location.y = mRandomGeneratorY(mRandomEngine);
					actor->Transform.Location.z = mRandomGeneratorZ(mRandomEngine);

					mGenerationCounter++;
				}
			};
			//���x���̍X�V�O���s�C�x���g�ɒǉ�
			mOwnerInterface.AddDoBeforeUpdateEvent(generationActor);
		}
	}

	const int& GetGenerationCounter()const
	{
		return mGenerationCounter;
	}
};