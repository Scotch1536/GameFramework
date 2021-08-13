#pragma once
#include <vector>
#include <memory>
#include <functional>

#include "CComponent.h"
#include "../Transform/CTransform.h"
#include "..\Library\LCMath.h"

class CTransform;


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
		CTransform Transform;
		XMFLOAT3 Direction;
		int Life;

		Particle(CTransform& parentTrans, const XMFLOAT3& direction, const int& life);
	};

private:
	std::function<void(const CParticleSystemComponent&,CTransform&)> mFunction;
	EType mType;
	int mLifeFlame;
	float mQuantity;
	std::vector<std::unique_ptr<Particle>> mParticle;
public:
	CTransform Transform;

	CParticleSystemComponent(CActor& owner, CTransform& parentTrans, std::function<void(const CParticleSystemComponent&, CTransform&)> func,
		EType type, int life, float qty, bool frameChoice, int priority = 100);

	void Update() override;
	void Move();
};
