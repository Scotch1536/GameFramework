#include "../Actor/CActor.h"
#include "../Library/LCMath.h"
#include "../Managers/CGameManager.h"

#include "CParticleGeneratorComponent.h"

//!
//! @file
//! @brief パーティクル生成コンポーネント類のソースファイル
//!

SParticleBase CParticleBaseGeneratorLine::GenerateParticleBase()
{
	SParticleBase result;
	result.Direction = mBaseAxis;
	result.StartPoint = { 0.0f,0.0f,0.0f };

	return result;
}

SParticleBase CParticleBaseGeneratorCone::GenerateParticleBase()
{
	SParticleBase result;

	XMFLOAT4X4 rotMTX;					//回転行列
	XMFLOAT4 quaternion;				//クオータニオン
	XMFLOAT3 rotationBaseDirection;		//回転基準となる方向
	XMFLOAT3 rotationAxis;				//回転軸

	float rotationBaseAngle = mRandomGeneratorRadian(mRandomEngine);			//回転基準を作るための回転角度（ラジアン）
	float rotationAngleRange = XMConvertToRadians(mCentralAngle / 2.0f);		//向きを作るための回転角度の範囲（ラジアン）

	//回転角度の乱数生成器
	std::uniform_real_distribution<float> rotationAngle(-rotationAngleRange , rotationAngleRange);

	//回転基準方向の計算処理
	rotationBaseDirection.x = cosf(rotationBaseAngle);
	rotationBaseDirection.y = 1.0f;
	rotationBaseDirection.z = sinf(rotationBaseAngle);

	LCMath::CalcFloat3Cross(mBaseAxis , rotationBaseDirection , rotationAxis);									//外積で回転軸を計算
	LCMath::CreateFromAxisAndAngleToQuaternion(rotationAxis , rotationAngle(mRandomEngine) , quaternion);		//回転行列の元となるクオータニオンを計算
	LCMath::CalcMatrixFromQuaternion(quaternion , rotMTX);														//回転行列作成
	LCMath::CalcFloat3MultplyMatrix(mBaseAxis , rotMTX , result.Direction);										//向きを計算
	result.StartPoint = { 0.0f,0.0f,0.0f };

	return result;
}

void CParticleGeneratorComponent::CParticle::Tick()
{
	//ライフタイム更新
	mLifetime -= CGameManager::GetInstance().GetDeltaTime();

	//ライフタイムが0以下ならデストロイ
	if(mLifetime <= 0)
	{
		Destroy();
		return;
	}

	//ロケーションにベロシティを加算
	LCMath::CalcFloat3Addition(Transform.Location , mVelocity , Transform.Location);
}

CParticleGeneratorComponent::CParticleGeneratorComponent(CActor& partner ,CTransform& parentTrans, std::function<void(CActor&)> particleBodyFunc ,
	float lifetime , float particleSpeed , float generationPerSecond ,
	CParticleBaseGenerator& particleBaseGenerator , int generationLimit):CComponent(partner) ,
	Transform(partner , parentTrans) , mParticleBodyGenerateFunction(particleBodyFunc) ,
	mParticleLifetime(lifetime) , mParticleSpeed(particleSpeed) , mGenerationLimit(generationLimit) ,
	mIncreasedValueOfGenerationGauge(generationPerSecond / 60.0f) , mParticleBaseGenerator(&particleBaseGenerator)
{}

void CParticleGeneratorComponent::Update()
{
	if(!mShouldUpdate)return;

	mGenerationGauge += mIncreasedValueOfGenerationGauge;		//ゲージに増加値を加算
	int numGeneration = mGenerationGauge / 1;					//生成数の計算

	if(numGeneration >= 1)
	{
		mGenerationGauge -= numGeneration;			//生成数分をゲージに減算

		//パーティクル生成の関数オブジェクトを作成
		auto generationParticle = [& , numGeneration]
		{
			for(int i = 0; i < numGeneration; ++i)
			{
				if(mGenerationLimit <= mGenerationCounter)break;		//生成カウンターが生成限界値以上ならループを抜ける

				GenerateParticle();										//パーティクル生成

				mParticleBodyGenerateFunction(*mParticleBuffer);		//パーティクルボディ生成

				mGenerationCounter++;									//生成カウンター加算
			}
		};

		//パーティクル生成の関数オブジェクトをレベルの更新前に実行する関数として登録
		mOwnerInterface.RequestAddDoBeforeUpdateFunction(generationParticle);
	}
}

void CParticleGeneratorComponent::GenerateParticle()
{
	XMFLOAT3 particleLocation;
	XMFLOAT3 particleVelocity;

	//パーティクルベース生成
	SParticleBase particleBase = mParticleBaseGenerator->GenerateParticleBase();

	//ロケーション計算
	LCMath::CalcFloat3Addition(Transform.GetWorldLocation() , particleBase.StartPoint , particleLocation);

	//回転行列作成処理
	XMFLOAT4X4 rotMTX = Transform.GetWorldMatrixResult();		//結果のマトリックス取得
	XMFLOAT3 bufVec;

	bufVec = LCMath::CalcFloat3Normalize({ rotMTX._11,rotMTX._12,rotMTX._13 });
	rotMTX._11 = bufVec.x;
	rotMTX._12 = bufVec.y;
	rotMTX._13 = bufVec.z;

	bufVec = LCMath::CalcFloat3Normalize({ rotMTX._21,rotMTX._22,rotMTX._23 });
	rotMTX._21 = bufVec.x;
	rotMTX._22 = bufVec.y;
	rotMTX._23 = bufVec.z;

	bufVec = LCMath::CalcFloat3Normalize({ rotMTX._31,rotMTX._32,rotMTX._33 });
	rotMTX._31 = bufVec.x;
	rotMTX._32 = bufVec.y;
	rotMTX._33 = bufVec.z;

	rotMTX._41 = 0.0f;
	rotMTX._42 = 0.0f;
	rotMTX._43 = 0.0f;
	rotMTX._44 = 1.0f;

	//向きを座標変換
	LCMath::CalcFloat3MultplyMatrix(particleBase.Direction , rotMTX , bufVec);

	//向きをベロシティに変換
	LCMath::CalcFloat3Scalar(bufVec , mParticleSpeed , particleVelocity);

	//パーティクル作成
	mParticleBuffer = new CParticle(CGameManager::GetInstance().GetLevelInterface() , particleVelocity , mParticleLifetime);
	mParticleBuffer->Transform.Location = particleLocation;
}