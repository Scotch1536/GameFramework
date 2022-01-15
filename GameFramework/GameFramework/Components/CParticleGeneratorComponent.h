#pragma once
#include <random>
#include <vector>
#include <memory>
#include <functional>
#include <DirectXMath.h>

#include "../Actor/CActor.h"
#include "../Transform/CTransform.h"

#include "CComponent.h"

using namespace DirectX;

//パーティクルベース構造体
struct SParticleBase
{
	XMFLOAT3 StartPoint;		//始点
	XMFLOAT3 Direction;			//向き
};

//向き生成ベースクラス
class CParticleBaseGenerator
{
protected:
	XMFLOAT3 mBaseAxis;			//基礎軸

public:
	CParticleBaseGenerator(XMFLOAT3 baseAxis):mBaseAxis(baseAxis) {};

	//向き生成
	virtual SParticleBase GenerateParticleBase() = 0;
};

//線形向き生成クラス
class CParticleBaseGeneratorLine :public CParticleBaseGenerator
{
public:
	CParticleBaseGeneratorLine(XMFLOAT3 baseAxis):CParticleBaseGenerator(baseAxis) {};

	SParticleBase GenerateParticleBase()override;
};

//円錐向き生成クラス
class CParticleBaseGeneratorCone :public CParticleBaseGenerator
{
private:
	std::random_device mRandomSeed;			//乱数デバイス
	std::mt19937 mRandomEngine;				//乱数アルゴリズム

	std::uniform_real_distribution<float> mRandomGeneratorRadian;		//ラジアン用乱数生成器

	float mCentralAngle;		//角度

public:
	CParticleBaseGeneratorCone(XMFLOAT3 baseAxis , float centralAngle):CParticleBaseGenerator(baseAxis) , mRandomEngine(mRandomSeed()) ,
		mCentralAngle(centralAngle) , mRandomGeneratorRadian(-1.0f , 1.0f)
	{};

	SParticleBase GenerateParticleBase()override;

	void SetAngle(float angle)
	{
		mCentralAngle = angle;
	}
};

//パーティクル生成機コンポーネント
class CParticleGeneratorComponent :public CComponent
{
	//パーティクルクラス
	class CParticle :public CActor
	{
	private:
		XMFLOAT3 mVelocity;			//ベロシティ
		float mLifetime;			//ライフタイム（秒）

	public:
		CParticle(ILevel& partner , XMFLOAT3 velocity , float lifetime):CActor(partner) ,
			mVelocity(velocity) , mLifetime(lifetime)
		{};

		void Tick()override;

		const XMFLOAT3& GetVelocity()const
		{
			return mVelocity;
		}

		void SetVelocity(XMFLOAT3 velocity)
		{
			mVelocity = velocity;
		}
	};

private:
	CParticle* mParticleBuffer;			//パーティクルを一時的に保持する変数

	std::unique_ptr<CParticleBaseGenerator> mParticleBaseGenerator;			//パーティクル生成機の形状

	std::function<void(CActor&)> mParticleBodyGenerateFunction;				//パーティクル生成時の実行関数

	XMFLOAT3 mBaseAxis;								//パーティクルシステムの基礎軸

	int mGenerationLimit;							//生成限界値(総数)
	int mGenerationCounter = 0;						//生成カウンター

	float mParticleLifetime;						//パーティクルのライフタイム（秒）
	float mGenerationGauge = 0.0f;					//生成ゲージ
	float mIncreasedValueOfGenerationGauge;			//生成ゲージの増加値（毎フレーム）
	float mParticleSpeed;							//パーティクルの速度（毎フレーム）

	bool mShouldUpdate = true;						//更新すべきか

	//更新
	void Update()override;

	//パーティクル生成
	void GenerateParticle();

public:
	CTransform Transform;		//トランスフォーム

	CParticleGeneratorComponent(CActor& partner , CTransform& parentTrans , std::function<void(CActor&)> particleBodyFunc ,
		float lifetime , float particleSpeed , float generationPerSecond ,
		CParticleBaseGenerator& directionGenerator , int generationLimit = 1000);

	bool SetShouldUpdate(bool flg)
	{
		mShouldUpdate = flg;
	}

};