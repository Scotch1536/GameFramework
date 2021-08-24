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

	if (fmodf(mQuantity, mFrameCount) == 0)
	{
		XMFLOAT3 direction;
		direction.x = float(mt() % 10);
		direction.y = float(mt() % 10);
		direction.z = float(mt() % 10);
		if (mt() % 2 == 0)
		{
			direction.x *= -1;
		}
		if (mt() % 2 == 0)
		{
			direction.y *= -1;
		}
		if (mt() % 2 == 0)
		{
			direction.z *= -1;
		}

		direction = LCMath::CalcFloat3Normalize(direction);

		Particle* particle = new Particle(mLevel, Transform, direction, mLifeFlame, mSpeed);

		auto func = [&] { mFunction(*particle, particle->Transform); };
		mOwnerInterface.RequestAddDoAfterUpdateFunction(func);
	}
}