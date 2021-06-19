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
	CAABBComponent(CActor& owner, int priority = 50) :CCollisionComponent(owner, priority) {}
};
