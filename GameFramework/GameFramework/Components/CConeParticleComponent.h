#pragma once
#include <vector>

#include "CParticleSystemComponent.h"

class CConeParticleComponent:public CParticleSystemComponent
{
private:
	std::vector<XMFLOAT3> mTemporaryDirection;
	XMFLOAT3 mDirection;
	float mDegree;

	void Update() override;
	bool ConvertDirection(XMFLOAT3 direction);
public:
	CConeParticleComponent(CActor& owner, ILevel& ownerLevel, CTransform& parentTrans, std::function<void(CParticleSystemComponent::Particle&, CTransform&)> func,
		 int life, float speed, XMFLOAT3 direction, float qty, float second, float degree);

};
