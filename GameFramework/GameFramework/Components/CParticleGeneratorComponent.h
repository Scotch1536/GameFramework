//!
//! @file
//! @brief パーティクル生成コンポーネント類のヘッダーファイル
//!

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

//! @brief パーティクルベース構造体
struct SParticleBase
{
	XMFLOAT3 StartPoint;		//!< 始点
	XMFLOAT3 Direction;			//!< 向き
};

//! @brief パーティクルベース生成クラス
class CParticleBaseGenerator
{
protected:
	XMFLOAT3 mBaseAxis;			//!< 基礎軸

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] baseAxis 基礎軸
	//!
	CParticleBaseGenerator(XMFLOAT3 baseAxis):mBaseAxis(baseAxis) {};

	//! @broef 向きベース生成
	virtual SParticleBase GenerateParticleBase() = 0;

};

//! @brief 線形パーティクルベース生成クラス
class CParticleBaseGeneratorLine :public CParticleBaseGenerator
{
public:
	//!
	//! @brief コンストラクタ
	//! @param[in] baseAxis 基礎軸
	//!
	CParticleBaseGeneratorLine(XMFLOAT3 baseAxis):CParticleBaseGenerator(baseAxis) {};

	//! @broef 向きベース生成
	SParticleBase GenerateParticleBase()override;

};

//! @brief 円錐パーティクルベース生成クラス
class CParticleBaseGeneratorCone :public CParticleBaseGenerator
{
private:
	std::random_device mRandomSeed;			//!< 乱数デバイス
	std::mt19937 mRandomEngine;				//!< 乱数アルゴリズム

	std::uniform_real_distribution<float> mRandomGeneratorRadian;		//!< ラジアン用乱数生成器

	float mCentralAngle;		//!< 中心角

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] baseAxis 基礎軸
	//! @param[in] centralAngle 中心角
	//!
	CParticleBaseGeneratorCone(XMFLOAT3 baseAxis , float centralAngle):CParticleBaseGenerator(baseAxis) , mRandomEngine(mRandomSeed()) ,
		mCentralAngle(centralAngle) , mRandomGeneratorRadian(-1.0f , 1.0f)
	{};

	//! @broef 向きベース生成
	SParticleBase GenerateParticleBase()override;

	void SetAngle(float angle)
	{
		mCentralAngle = angle;
	}

};

//! @brief パーティクル生成コンポーネント
class CParticleGeneratorComponent :public CComponent
{
	//! @brief パーティクルクラス
	class CParticle :public CActor
	{
	private:
		XMFLOAT3 mVelocity;			//!< ベロシティ
		float mLifetime;			//!< ライフタイム（秒）

	public:
		//!
		//! @brief コンストラクタ
		//! @param[in] partner このアクターの所有レベル
		//! @param[in] velocity ベロシティ
		//! @param[in] lifetime ライフタイム
		//!
		CParticle(ILevel& partner , XMFLOAT3 velocity , float lifetime):CActor(partner) ,
			mVelocity(velocity) , mLifetime(lifetime)
		{};

		//! @brief ティック（毎フレーム行う追加処理）
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
	CParticle* mParticleBuffer;												//!< パーティクルを一時的に保持する変数

	std::unique_ptr<CParticleBaseGenerator> mParticleBaseGenerator;			//!< パーティクルベース生成器

	std::function<void(CActor&)> mParticleBodyGenerateFunction;				//!< パーティクルの本体部分の生成関数

	XMFLOAT3 mBaseAxis;								//!< パーティクル生成器の基礎軸

	int mGenerationLimit;							//!< 生成限界値(総数)
	int mGenerationCounter = 0;						//!< 生成カウンター

	float mParticleLifetime;						//!< パーティクルのライフタイム（秒）
	float mGenerationGauge = 0.0f;					//!< 生成ゲージ
	float mIncreasedValueOfGenerationGauge;			//!< 生成ゲージの増加値（毎フレーム）
	float mParticleSpeed;							//!< パーティクルの速度（毎フレーム）

	bool mShouldUpdate = true;						//!< 更新すべきか

	//! @brief 更新
	void Update()override;

	//! @brief パーティクル生成
	void GenerateParticle();

public:
	CTransform Transform;		//!< トランスフォーム

	//!
	//! @brief コンストラクタ
	//! @param[in] partner このコンポーネントを所有するアクター
	//! @param[in] parentTrans 親のトランスフォーム
	//! @param[in] particleBodyFunc パーティクルの本体部分の生成関数オブジェクト
	//! @param[in] lifetime ライフタイム
	//! @param[in] particleSpeed パーティクルの速度（毎フレーム）
	//! @param[in] generationPerSecond 1秒間に生成するパーティクルの数
	//! @param[in] particleBaseGenerator パーティクルベース生成器
	//! @param[in] generationLimit 生成限界値(総数)
	//!
	CParticleGeneratorComponent(CActor& partner , CTransform& parentTrans , std::function<void(CActor&)> particleBodyFunc ,
		float lifetime , float particleSpeed , float generationPerSecond ,
		CParticleBaseGenerator& particleBaseGenerator , int generationLimit = 1000);

	void SetShouldUpdate(bool flg)
	{
		mShouldUpdate = flg;
	}

};