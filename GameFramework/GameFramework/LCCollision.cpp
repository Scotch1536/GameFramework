#include "LCCollision.h"
#include "../GameFramework/Components/CCollisionComponent.h"
#include "Components/CAABBComponent.h"

bool LCCollision::Intersect(const XMFLOAT3& AMin, const XMFLOAT3& AMax, const XMFLOAT3& BMin, const XMFLOAT3& BMax)
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

bool LCCollision::Contains(const XMFLOAT3& AMin, const XMFLOAT3& AMax, const XMFLOAT3& point)
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