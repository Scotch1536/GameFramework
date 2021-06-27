#pragma once
#include <DirectXMath.h>

using namespace DirectX;

static class LCCollision
{
public:

	//AABB
	static bool Intersect(const XMFLOAT3& AMin, const XMFLOAT3& AMax, const XMFLOAT3& BMin, const XMFLOAT3& BMax);
	static bool Contains(const XMFLOAT3& AMin, const XMFLOAT3& AMax, const XMFLOAT3& point);
	//Sphere
	static bool Intersect(const XMFLOAT3& ACenter,const float& ARadius, const XMFLOAT3& BCenter, const float& BRadius);
};
