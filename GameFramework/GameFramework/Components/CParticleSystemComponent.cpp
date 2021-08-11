#include <random>

#include "CParticleSystemComponent.h"
#include "CSphereMeshComponent.h"

CParticleSystemComponent::CParticleSystemComponent(CActor& owner, CTransform& parentTrans, std::function<void(CParticleSystemComponent::Particle &) > func
	, EType type, int life, float qty, bool frameChoice, int priority)
	:CComponent(owner, priority), Transform(parentTrans), mType(type), mLifeValue(life),mFunction(func)
{
	//trueÇ»ÇÁÇPÉtÉåÅ[ÉÄÇ≤Ç∆Ç…ê∂ê¨ falseÇ»ÇÁÇPïb
	if (frameChoice)
	{
		mQuantity = qty;
	}
	else
	{
		mQuantity = qty / 60;
	}
}

void CParticleSystemComponent::Update()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	bool shouldJudge = false;
	for (float q = 0; q < mQuantity; q++)
	{
		mParticle.emplace_back();
		mParticle.back().Direction.x = mt() % 50;
		mParticle.back().Direction.y = mt() % 50;
		mParticle.back().Direction.z = mt() % 50;
		mParticle.back().Life = mLifeValue;
		mFunction(mParticle.back());
	}

	Move();

	for (auto itr = mParticle.begin(); itr != mParticle.end(); itr++)
	{
		if ((*itr).Life <= 0)
		{
			mParticle.erase(itr);
			shouldJudge = true;
		}
	}
	if (shouldJudge)
	{
		mParticle.shrink_to_fit();
	}
}

void CParticleSystemComponent::Move()
{
	for (auto& p : mParticle)
	{
		p.Transform.Location.x = p.Transform.Location.x + p.Direction.x;
		p.Transform.Location.y = p.Transform.Location.y + p.Direction.y;
		p.Transform.Location.z = p.Transform.Location.z + p.Direction.z;
		p.Life--;
	}
}