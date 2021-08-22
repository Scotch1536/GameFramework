#include <random>

#include "../Level/CLevel.h"
#include "../Actor/CActor.h"
#include "CParticleSystemComponent.h"
#include "CSphereMeshComponent.h"

#include "../Transform/CTransform.h"

CParticleSystemComponent::Particle::Particle(ILevel& owner,CTransform& parentTrans, const XMFLOAT3& direction, const int& life) :CActor(owner),
	Transform(*this, parentTrans), Direction(direction), Life(life) {}

CParticleSystemComponent::CParticleSystemComponent(CActor& owner, ILevel& ownerLevel, CTransform& parentTrans, std::function<void(CParticleSystemComponent::Particle&, CTransform&) > func
	, EType type, int life, float qty,float speed, bool frameChoice, int priority)
	: CComponent(owner, priority), Transform(owner, parentTrans),mLevel(ownerLevel), mType(type), mLifeFlame(life), mFunction(func),mSpeed(speed)
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
	for (float q = 0; q < mQuantity; q++)
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

		mParticle.emplace_back(new Particle(mLevel,Transform, direction, mLifeFlame));	

		auto func = [&] { mFunction(*mParticle.back(), mParticle.back()->Transform); };
		mOwnerInterface.RequestAddDoAfterUpdateFunction(func);
	}

	Move();

}

void CParticleSystemComponent::Move()
{
	bool shouldJudge = false;
	if (mParticle.size() != 0)
	{
		for (auto& p : mParticle)
		{
			XMFLOAT3 worldLoc = p->Transform.GetWorldLocation();
			p->Transform.Location.x += p->Direction.x * mSpeed;
			p->Transform.Location.y += p->Direction.y * mSpeed;
			p->Transform.Location.z += p->Direction.z * mSpeed;
			p->Life--;
		}

		for (auto itr = mParticle.begin(); itr != mParticle.end();)
		{
			if ((*itr)->Life <= 0)
			{
				(*itr)->Destroy();
				itr = mParticle.erase(itr);
				shouldJudge = true;
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
}