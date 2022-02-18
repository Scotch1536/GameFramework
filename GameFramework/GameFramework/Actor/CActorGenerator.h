//!
//! @file
//! @brief アクタージェネレーターのヘッダーファイル
//!

#pragma once
#include <random>
#include <functional>

#include "../Level/CLevel.h"

#include "CActor.h"

//! @brief アクタージェネレータークラス
class CActorGenerator :public CActor
{
private:
	std::function<CActor*()> mInstantiationEvent;					//!< インスタンス化イベント

	std::random_device mRandomSeed;									//!< 乱数デバイス
	std::mt19937 mRandomEngine;										//!< 乱数アルゴリズム

	std::uniform_real_distribution<float> mRandomGeneratorX;		//!< 乱数生成器X
	std::uniform_real_distribution<float> mRandomGeneratorY;		//!< 乱数生成器Y
	std::uniform_real_distribution<float> mRandomGeneratorZ;		//!< 乱数生成器Z

	int mGenerationLimit;											//!< 生成限界値（総数）
	int mGenerationCounter = 0;										//!< 生成カウンター

	float mGenerationGauge = 0.0f;									//!< 生成ゲージ
	float mIncreasedValueOfGenerationGauge;							//!< 生成ゲージの増加値（毎フレーム）

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] partner このアクターを所有するレベル
	//! @param[in] instantiationEvent インスタンス化イベント
	//! @param[in] minRange 生成範囲の最小値
	//! @param[in] maxRange 生成範囲の最大値
	//! @param[in] generationPerSecond 1秒あたりの生成数
	//! @param[in] generationLimit 生成限界値（総数）
	//!
	CActorGenerator(ILevel& partner , std::function<CActor*()> instantiationEvent , XMFLOAT3 minRange , XMFLOAT3 maxRange , float generationPerSecond , int generationLimit = 1000)
		:CActor(partner) , mInstantiationEvent(instantiationEvent) ,
		mRandomEngine(mRandomSeed()) , mRandomGeneratorX(minRange.x , maxRange.x) ,
		mRandomGeneratorY(minRange.y , maxRange.y) , mRandomGeneratorZ(minRange.z , maxRange.z) ,
		mGenerationLimit(generationLimit) , mIncreasedValueOfGenerationGauge(generationPerSecond / 60.0f)
	{}

	//! @brief ティック（毎フレーム行う追加処理）
	void Tick()override
	{
		//ゲージの更新
		mGenerationGauge += mIncreasedValueOfGenerationGauge;

		//生成数算出
		int numGeneration = mGenerationGauge / 1;

		//生成数が1以上なら
		if(numGeneration >= 1)
		{
			//ゲージの更新
			mGenerationGauge -= numGeneration;

			//アクター生成の関数オブジェクト作成
			auto generationActor = [& , numGeneration]
			{
				for(int i = 0; i < numGeneration; ++i)
				{
					if(mGenerationLimit <= mGenerationCounter)break;

					//インスタンス化
					CActor* actor = mInstantiationEvent();

					//ロケーションの算出
					actor->Transform.Location.x = mRandomGeneratorX(mRandomEngine);
					actor->Transform.Location.y = mRandomGeneratorY(mRandomEngine);
					actor->Transform.Location.z = mRandomGeneratorZ(mRandomEngine);

					mGenerationCounter++;
				}
			};
			//レベルの更新前実行イベントに追加
			mOwnerInterface.AddDoBeforeUpdateEvent(generationActor);
		}
	}

	const int& GetGenerationCounter()const
	{
		return mGenerationCounter;
	}
};