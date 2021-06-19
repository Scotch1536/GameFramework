#include "LCCollision.h"

bool LCCollision::Intersect(XMFLOAT3& AMin, XMFLOAT3& AMax, XMFLOAT3& BMin, XMFLOAT3& BMax)
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

bool LCCollision::Contains(XMFLOAT3& AMin, XMFLOAT3& AMax, XMFLOAT3& point)
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