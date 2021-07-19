#pragma once
#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Components/CColliderComponent.h"

class CDice :public CActor
{
private:
	XMFLOAT3 &mPoint;
	XMFLOAT4 mStartQua;
	std::unique_ptr<XMFLOAT4> mGoalQua;

	float mAlpha = 0.f;
	float mIncrementAlpha = 0.f;
public:
	CDice(CLevel& owner,XMFLOAT3& pointLocation);

	void Move();
	void Tick()override;
};

