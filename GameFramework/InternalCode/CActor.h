#pragma once
#include <vector>
#include <memory>

#include "CComponent.h"
#include "CLevel.h"
#include "CTransform.h"

class CActor
{
private:
	std::vector<std::unique_ptr<CComponent>> mComponents;
	CTransform mTransform;
	ILevelMethod& mOwnerMethod;
public:
	CActor(CLevel& owner);

	void AddComponent(CComponent* component);
	void Update();
	void Destroy();
};