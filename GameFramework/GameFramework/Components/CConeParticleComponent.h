#pragma once
#include <vector>

#include "CParticleSystemComponent.h"

class CConeParticleComponent:public CParticleSystemComponent
{
private:
	XMFLOAT3 mDefaultDirection;
	XMFLOAT3 mDirection;
	float mDegree;

	void Update() override;
	int ColcMatrixOfConvert(const XMFLOAT3& direction, XMFLOAT4X4& resultMTX);
public:
	CConeParticleComponent(CActor& owner, ILevel& ownerLevel, CTransform& parentTrans, std::function<void(CParticleSystemComponent::Particle&, CTransform&)> func,
		 int life, float speed, XMFLOAT3 direction, float qty, float second, float degree);

};
