#pragma once
#include <vector>
#include <functional>

#include "CComponent.h"
#include "../Transform/CTransform.h"
#include "..\Library\LCMath.h"

class CParticleSystemComponent :public CComponent  
{
public:
	enum class EType
	{
		SPHERE,
		RADIATION,
	};
	
	struct Particle 
	{
		CTransform& Transform;
		XMFLOAT3 Direction;
		int Life;
	};
private:
	std::function<void(CParticleSystemComponent::Particle&)> mFunction;
	EType mType;
	float mLifeValue;
	float mQuantity;
	std::vector<Particle> mParticle;
public:
	CTransform Transform;

	CParticleSystemComponent(CActor& owner, CTransform& parentTrans, std::function<void(CParticleSystemComponent::Particle&)> func,
		EType type, int life, float qty, bool frameChoice, int priority = 100);

	void Update() override;
	void Move();
};
