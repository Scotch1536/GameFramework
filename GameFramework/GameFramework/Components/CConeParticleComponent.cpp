#include <random>

#include "CConeParticleComponent.h"
#include "../ExternalCode/dx11mathutil.h"

CConeParticleComponent::CConeParticleComponent(CActor& owner, ILevel& ownerLevel, CTransform& parentTrans, std::function<void(CParticleSystemComponent::Particle&, CTransform&)> func,
	int life, float speed, XMFLOAT3 direction, float qty, float second, float degree)
	:CParticleSystemComponent(owner, ownerLevel, parentTrans, func, life, qty, speed, second), mDegree(degree)
{
	LCMath::CalcFloat3Normalize(direction, mDefaultDirection);
	mDirection = mDefaultDirection;
}

void CConeParticleComponent::Update()
{
	std::random_device rd;
	std::mt19937 mt(rd());

	if (!Transform.Rotation.GetIsSameAngleToBeforeFrame())
	{
		XMFLOAT4X4 rot = Transform.Rotation.GenerateMatrix();
		LCMath::CalcFloat3MultplyMatrix(mDefaultDirection, rot, mDirection);
	}

	mGenerationGauge += mQuantity;
	int numGeneration = mGenerationGauge / 1;

	if (numGeneration >= 1)
	{
		mGenerationGauge -= numGeneration;

		XMFLOAT3 defaultDirection = { 0,1,0 };
		XMFLOAT3 direction;
		XMFLOAT4X4 rotX;
		XMFLOAT4X4 rotZ;
		XMFLOAT4X4 rotMTX;
		XMFLOAT4X4 convertMTX;
		std::uniform_real_distribution urd(-mDegree / 2, mDegree / 2);

		bool shouldConvert = ColcMatrixOfConvert(defaultDirection, convertMTX);

		for (int i = 0; i < numGeneration; ++i)
		{

			DX11MtxRotationAxis({ 1,0,0 }, urd(mt), rotX);
			DX11MtxRotationAxis({ 0,0,1 }, urd(mt), rotZ);
			DX11MtxMultiply(rotMTX, rotX, rotZ);
			DX11Vec3MulMatrix(direction, defaultDirection, rotMTX);

			if (shouldConvert == 1)	LCMath::CalcFloat3MultplyMatrix(direction, convertMTX, direction);
			else if (shouldConvert == 2)	LCMath::CalcFloat3Scalar(direction, -1.f, direction);

			if (shouldConvert)
			{
				//direction = LCMath::CalcFloat3Normalize(direction);
				auto func = [&, direction]
				{
					Particle *particle = new Particle(mLevel, direction, mFunction, mLifeFlame, mSpeed);
					particle->Transform.Location = Transform.GetWorldLocation();
				};
				mOwnerInterface.RequestAddDoBeforeUpdateFunction(func);
			}
			else
			{
				auto func = [&, direction]
				{
					Particle *particle = new Particle(mLevel, direction, mFunction, mLifeFlame, mSpeed);
					particle->Transform.Location = Transform.GetWorldLocation();
				};
				mOwnerInterface.RequestAddDoBeforeUpdateFunction(func);
			}
		}
	}

}

int CConeParticleComponent::ColcMatrixOfConvert(const XMFLOAT3& direction, XMFLOAT4X4& resultMTX)
{
	XMFLOAT4 mulQua;
	XMFLOAT4X4 MTX;
	XMFLOAT3 axis;
	float angle;

	//クォータニオンに必要な角度を計算
	LCMath::CalcFloat3Dot(direction, mDirection, angle);

	/*
	結果が1(小数点がはみ出ることがあるので1以上)ならベクトル同士が平行なので終了
	-1以下なら-1にする
	*/
	if (angle >= 1.0f)return 0;
	else if (angle <= -1.0f)
	{
		return 2;
	}

	//角度を求める
	angle = std::acosf(angle);

	//外積で法線求める
	//クォータニオンに必要な軸を計算
	LCMath::CalcFloat3Cross(direction, mDirection, axis);

	//クォータニオン作成
	LCMath::CreateFromAxisAndAngleToQuaternion(axis, angle, mulQua);

	//クォータニオンを回転行列に変換
	LCMath::CalcMatrixFromQuaternion(mulQua, resultMTX);

	//回転行列とdirectionをかけてdirectionに代入
	//LCMath::CalcFloat3MultplyMatrix(direction, MTX, direction);

	return 1;
}