#pragma once
#include <vector>
#include <memory>

#include "CComponent.h"
#include "CLevel.h"
#include "CTransform.h"

class IActorMethod
{
public:
	virtual ~IActorMethod() {};
	virtual void AddComponent(CComponent& component) = 0;
};

class CActor :public IActorMethod
{
private:
	std::vector<std::unique_ptr<CComponent>> mComponents;
	CTransform mTransform;
	ILevelMethod& mOwnerMethod;
public:
	CActor(CLevel& owner);

	void AddComponent(CComponent& component)override;
	void Update();
	void Destroy();
};