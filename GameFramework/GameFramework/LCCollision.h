#pragma once
#include <DirectXMath.h>

using namespace DirectX;

static class LCCollision
{
public:
	static bool Intersect(XMFLOAT3& AMin, XMFLOAT3& AMax, XMFLOAT3& BMin, XMFLOAT3& BMax);
	static bool Contains(XMFLOAT3& AMin, XMFLOAT3& AMax, XMFLOAT3& point);
};
