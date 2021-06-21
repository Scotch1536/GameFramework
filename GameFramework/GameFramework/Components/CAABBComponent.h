#pragma once
#include <DirectXMath.h>
#include "CCollisionComponent.h"

using namespace DirectX;

class CAABBComponent :public CCollisionComponent
{
private:
	XMFLOAT3 mMin;
	XMFLOAT3 mMax;
public:
	CAABBComponent(CActor& owner, int priority = 40);

	void Update() override;
};
