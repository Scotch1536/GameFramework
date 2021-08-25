#pragma once

#include "CParticleSystemComponent.h"

class CConeParticleComponent:public CParticleSystemComponent
{
private:
	XMFLOAT3& mDirection;

	void Update() override;
public:
	CConeParticleComponent(CActor& owner, ILevel& ownerLevel, CTransform& parentTrans, std::function<void(CParticleSystemComponent::Particle&, CTransform&)> func,
		 int life, float speed, XMFLOAT3 direction, float qty, float second);

};
