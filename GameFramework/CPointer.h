#pragma once
#include <memory>
#include "GameFramework/Actor/CActor.h"

class CFighter;

class CPointer :public CActor
{
private:
	CFighter& mOwner;
	std::unique_ptr<XMFLOAT3> mInitLocation;

	float mInitMousePosX;
	float mInitMousePosY;
	float mDiffPosX;
	float mDiffPosY;
public:
	CPointer(ILevel& partner , CFighter& owner);

	void Tick()override;
};

