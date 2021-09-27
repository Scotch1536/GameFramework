#include "../Level/CLevel.h"
#include "../Actor/CActor.h"
#include "CParticleSystemComponent.h"
#include "CConeParticleComponent.h"
#include "CSphereMeshComponent.h"

#include "../Transform/CTransform.h"

CParticleSystemComponent::Particle::Particle(ILevel& owner, const XMFLOAT3& direction, std::function<void(CParticleSystemComponent::Particle&, CTransform&)> function, const int& life, const float& speed) 
	:CActor(owner), Direction(direction), Life(life), Speed(speed) 
{
	function(*this, Transform);	
	AddTag("Particle");
}

void CParticleSystemComponent::Particle::Tick()
{
	Transform.Location.x += Direction.x * Speed;
	Transform.Location.y += Direction.y * Speed;
	Transform.Location.z += Direction.z * Speed;
	Life--;

	if (Life <= 0)
	{
		Destroy();
	}
}

CParticleSystemComponent::CParticleSystemComponent(CActor& owner, ILevel& ownerLevel, CTransform& parentTrans, std::function<void(CParticleSystemComponent::Particle&, CTransform&)> func
	, int life, float qty, float speed, float second, int priority)
	: CComponent(owner, priority), Transform(owner, parentTrans), mLevel(ownerLevel), mLifeFlame(life), mFunction(func), mSpeed(speed)
{
	float createTime = second * 60;
	mQuantity = qty / createTime;
}

void CParticleSystemComponent::Create(CActor& owner, ILevel& ownerLevel, CTransform& parentTrans, std::function<void(CParticleSystemComponent::Particle&, CTransform&)> func,
	int life, float speed, float qty, float degree, XMFLOAT3 direction, float second)
{
	new CConeParticleComponent(owner, ownerLevel, parentTrans, func, life, speed, direction, qty, second, degree);
}
