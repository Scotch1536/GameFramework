#pragma once
#include <DirectXMath.h>
#include <vector>

using namespace DirectX;

static class LCCollision
{
public:

	//AABB     Intersect:�����@�@�@�@Contains:����
	static bool IsCollide(const XMFLOAT3& AMin, const XMFLOAT3& AMax, const XMFLOAT3& BMin, const XMFLOAT3& BMax);
	static bool IsCollide(const XMFLOAT3& AMin, const XMFLOAT3& AMax, const XMFLOAT3& point);
	//Sphere   Intersect:����
	static bool IsCollide(const XMFLOAT3& ACenter,const float& ARadius, const XMFLOAT3& BCenter, const float& BRadius);

};
