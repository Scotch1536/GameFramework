#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class CCollisionComponent;
class CAABBComponent;

static class LCCollision
{
public:

	//AABB
	static bool Intersect(const XMFLOAT3& AMin, const XMFLOAT3& AMax, const XMFLOAT3& BMin, const XMFLOAT3& BMax);
	static bool Contains(const XMFLOAT3& AMin, const XMFLOAT3& AMax, const XMFLOAT3& point);
	//Sphere
};
