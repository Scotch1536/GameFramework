#include <random>

#include "CParticleSystemComponent.h"
#include "CSphereMeshComponent.h"

#include "../Transform/CTransform.h"


CParticleSystemComponent::Particle::Particle(CTransform& parentTrans, const XMFLOAT3& direction, const int& life) :Transform(parentTrans), Direction(direction), Life(life) {}

CParticleSystemComponent::CParticleSystemComponent(CActor& owner, CTransform& parentTrans, std::function<void(const CParticleSystemComponent&, CTransform&) > func
	, EType type, int life, float qty, bool frameChoice, int priority)
	:CComponent(owner, priority), Transform(parentTrans), mType(type), mLifeFlame(life),mFunction(func)
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
		XMFLOAT3 direction;
		direction.x = float(mt() % 50);
		direction.y = float(mt() % 50);
		direction.z = float(mt() % 50);
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

		mParticle.emplace_back(new Particle(Transform, direction, mLifeFlame));

		mFunction(*this,mParticle.back()->Transform);
	}

	Move();

	for (auto itr = mParticle.begin(); itr != mParticle.end();)
	{
		if ((*itr)->Life <= 0)
		{
			itr = mParticle.erase(itr);
			shouldJudge = true;
			break;
		}
		else
		{
			itr++;
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
		p->Transform.Location.x = p->Transform.Location.x + p->Direction.x;
		p->Transform.Location.y = p->Transform.Location.y + p->Direction.y;
		p->Transform.Location.z = p->Transform.Location.z + p->Direction.z;
		p->Life--;
	}
}