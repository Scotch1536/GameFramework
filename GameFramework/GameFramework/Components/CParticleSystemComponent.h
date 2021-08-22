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
	enum class EType
	{
		SPHERE,
		RADIATION,
	};

	class Particle:public CActor
	{
	public:
		IRender* MeshComponent;
		CTransform Transform;
		XMFLOAT3 Direction;

		int Life;

		Particle(ILevel& owner, CTransform& parentTrans, const XMFLOAT3& direction, const int& life);
	};

private:
	std::vector<Particle*> mParticle;
	std::function<void(CParticleSystemComponent::Particle&,CTransform&)> mFunction;

	ILevel& mLevel;
	EType mType;

	int mLifeFlame;
	float mQuantity;
	float mSpeed;
public:
	CTransform Transform;

	CParticleSystemComponent(CActor& owner, ILevel& ownerLevel, CTransform& parentTrans, std::function<void(CParticleSystemComponent::Particle&, CTransform&)> func,
		EType type, int life, float qty,float speed, bool frameChoice, int priority = 1);

	void Update() override;
	void Move();
};
