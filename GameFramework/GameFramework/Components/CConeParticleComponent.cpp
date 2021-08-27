#include <random>

#include "CConeParticleComponent.h"
#include "../ExternalCode/dx11mathutil.h"

CConeParticleComponent::CConeParticleComponent(CActor& owner, ILevel& ownerLevel, CTransform& parentTrans, std::function<void(CParticleSystemComponent::Particle&, CTransform&)> func,
	int life, float speed, XMFLOAT3 direction, float qty, float second, float degree)
	:CParticleSystemComponent(owner, ownerLevel, parentTrans, func, life, qty, speed, second), mDirection(direction), mDegree(degree)
{}

void CConeParticleComponent::Update()
{
	std::random_device rd;
	std::mt19937 mt(rd());

	if (mQuantity >= 1)
	{
		for (int q = 0; q < mQuantity; q++)
		{
			XMFLOAT3 defaultDirection = { 0,1,0 };
			XMFLOAT3 direction;
			XMFLOAT4X4 rotX;
			XMFLOAT4X4 rotZ;
			XMFLOAT4X4 rotMTX;
			std::uniform_real_distribution urd(-mDegree / 2, mDegree / 2);

			DX11MtxRotationAxis({ 1,0,0 }, urd(mt), rotX);
			DX11MtxRotationAxis({ 0,0,1 }, urd(mt), rotZ);
			DX11MtxMultiply(rotMTX, rotX, rotZ);
			DX11Vec3MulMatrix(direction, defaultDirection, rotMTX);

			direction = LCMath::CalcFloat3Normalize(direction);

			auto func = [&] {new Particle(mLevel, Transform, direction, mFunction, mLifeFlame, mSpeed); };
			mOwnerInterface.RequestAddDoAfterUpdateFunction(func);
		}
	}
	else
	{
		if (fmodf(mFrameCount, mQuantity) == 0)
		{
			XMFLOAT3 direction;
			direction.x = float(mt() % 10) + mDirection.x;
			direction.y = float(mt() % 10) + mDirection.y;
			direction.z = float(mt() % 10) + mDirection.z;

			direction = LCMath::CalcFloat3Normalize(direction);

			new Particle(mLevel, Transform, direction, mFunction, mLifeFlame, mSpeed);
		}
	}
	++mFrameCount;
	if (mFrameCount >= 36000) mFrameCount = 0;
}

bool CConeParticleComponent::ConvertDirection(XMFLOAT3 direction)
{
	XMFLOAT4 mulQua;
	XMFLOAT3 vec, axis, eulerAngles;
	float angle;

	//クォータニオンに必要な角度を計算
	LCMath::CalcFloat3Dot(direction, mDirection, angle);

	/*
	結果が1(小数点がはみ出ることがあるので1以上)ならベクトル同士が平行なので終了
	-1以下なら-1にする
	*/
	if (angle >= 1.0f)return;
	else if (angle < -1.0f)
	{
		direction.x *= -1;
		direction.y *= -1;
		direction.z *= -1;

		return true;
	}

	//角度を求める
	angle = std::acosf(angle);

	DX11MtxRotationAxis();
	//クォータニオンに必要な軸を計算
	LCMath::CalcFloat3Cross(mPartner.GetForwardVector(), vec, axis);

	//クォータニオン作成
	LCMath::CreateFromAxisAndAngleToQuaternion(axis, angle, mulQua);
}