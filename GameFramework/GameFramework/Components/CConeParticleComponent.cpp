#include <random>

#include "CConeParticleComponent.h"

CConeParticleComponent::CConeParticleComponent(CActor& owner, ILevel& ownerLevel, CTransform& parentTrans, std::function<void(CParticleSystemComponent::Particle&, CTransform&)> func,
	int life, float speed, XMFLOAT3 direction, float qty, float second)
	:CParticleSystemComponent(owner, ownerLevel, parentTrans, func, life, qty, speed, second), mDirection(direction)
{}

void CConeParticleComponent::Update()
{
	std::random_device rd;
	std::mt19937 mt(rd());

	if (mQuantity >= 1)
	{
		for (int q = 0; q < mQuantity; q++)
		{
			XMFLOAT3 direction;
			direction.x = float(mt() % 5) + mDirection.x;
			direction.y = float(mt() % 5) + mDirection.y;
			direction.z = float(mt() % 5) + mDirection.z;

			direction = LCMath::CalcFloat3Normalize(direction);

			new Particle(mLevel, Transform, direction, mFunction, mLifeFlame, mSpeed);
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