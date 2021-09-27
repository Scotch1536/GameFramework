#pragma once
#include <vector>
#include <memory>
#include <functional>

#include "CComponent.h"
#include "../Components/CRenderComponent.h"
#include "../Actor/CActor.h"
#include "../Transform/CTransform.h"
#include "../Library\LCMath.h"

class CTransform;

class CParticleSystemComponent :public CComponent
{
public:

	class Particle :public CActor
	{
	public:
		IRender* MeshComponent;
		XMFLOAT3 Direction;

		int Life;
		float Speed;

		Particle(ILevel& owner, const XMFLOAT3& direction, std::function<void(CParticleSystemComponent::Particle&, CTransform&)> func, const int& life, const float& speed);
		void Tick() override;
	};

private:
	std::vector<Particle*> mParticle;

protected:
	std::function<void(CParticleSystemComponent::Particle&, CTransform&)> mFunction;
	ILevel& mLevel;
	CTransform Transform;

	float mQuantity;
	float mSpeed;
	float mGenerationGauge = 0.f;
	int mLifeFlame;

	CParticleSystemComponent(CActor& owner, ILevel& ownerLevel, CTransform& parentTrans, std::function<void(CParticleSystemComponent::Particle&, CTransform&)> func,
		int life, float qty, float speed, float second, int priority = 1);
public:

	static void Create(CActor& owner, ILevel& ownerLevel, CTransform& parentTrans, std::function<void(CParticleSystemComponent::Particle&, CTransform&)> func,
		int life, float speed, float qty,float degree, XMFLOAT3 direction = {0,1,0}, float second = 1);
};
