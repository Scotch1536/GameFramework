#pragma once
#include <vector>
#include <memory>

#include "CComponent.h"
#include "CTransform.h"

class ILevel;
class CLevel;

class IActor
{
public:
	virtual ~IActor() {};
	virtual void AddComponent(CComponent& component) = 0;
};

class CActor :public IActor
{
private:
	std::vector<std::unique_ptr<CComponent>> mComponents;
	CTransform mTransform;
	ILevel& mOwnerInterface;
public:
	CActor(CLevel& owner);

	void AddComponent(CComponent& component)override;
	void Update();
	void Destroy();
};