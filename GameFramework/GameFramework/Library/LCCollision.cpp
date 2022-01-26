#include <algorithm>

#include "LCCollision.h"

bool LCCollision::IsCollide(const XMFLOAT3& AMin, const XMFLOAT3& AMax, const XMFLOAT3& BMin, const XMFLOAT3& BMax)
{
	if (AMax.x < BMin.x ||
		AMax.y < BMin.y ||
		AMax.z < BMin.z ||
		BMax.x < AMin.x ||
		BMax.y < AMin.y ||
		BMax.z < AMin.z)
	{
		return false;
	}
	return true;
}

bool LCCollision::IsCollide(const XMFLOAT3& AMin, const XMFLOAT3& AMax, const XMFLOAT3& point)
{
	if (point.x<AMin.x ||
		point.y<AMin.y ||
		point.z<AMin.z ||
		point.x>AMax.x ||
		point.y>AMax.y ||
		point.z>AMax.z)
	{
		return false;
	}
	return true;
}

bool LCCollision::IsCollide(const XMFLOAT3& ACenter, const float& ARadius, const XMFLOAT3& BCenter, const float& BRadius)
{
	float xAns = ACenter.x - BCenter.x;
	float yAns = ACenter.y - BCenter.y;
	float zAns = ACenter.z - BCenter.z;

	float sumRadius = ARadius + BRadius;

	return (xAns * xAns) + (yAns * yAns) + (zAns * zAns) <= (sumRadius * sumRadius);
}

bool LCCollision::IsCollide(const XMFLOAT3& AMin, const XMFLOAT3& AMax, const XMFLOAT3& BCenter, const float& BRadius)
{
	//Ž²‚Ì·‚ðŽZo
	float dx = (std::max)(AMin.x - BCenter.x, 0.0f);
	dx = (std::max)(dx, BCenter.x - AMax.x);
	float dy = (std::max)(AMin.y - BCenter.y, 0.0f);
	dy = (std::max)(dy, BCenter.y - AMax.y);
	float dz = (std::max)(AMin.z - BCenter.z, 0.0f);
	dz = (std::max)(dz, BCenter.z - AMax.z);

	float dist = dx * dx + dy * dy + dz * dz;

	return dist <= (BRadius * BRadius);
}
