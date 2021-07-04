#include "LCCollision.h"

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

bool LCCollision::Intersect(const XMFLOAT3& ACenter, const float& ARadius, const XMFLOAT3& BCenter, const float& BRadius)
{
	float xAns = ACenter.x - BCenter.x;
	float yAns = ACenter.y - BCenter.y;
	float zAns = ACenter.z - BCenter.z;

	float dist =(xAns * xAns) + (yAns * yAns) + (zAns * zAns);
	float sumRadius = ARadius + BRadius;
	return dist <= (sumRadius*sumRadius);
}

void LCCollision::CalcMinMaxOfMeshes(const std::vector<Mesh>& meshes, XMFLOAT3& min, XMFLOAT3& max)
{
	for (auto m : meshes)
	{
		for (auto v : m.m_vertices)
		{
			if (min.x > v.m_Pos.x)	min.x = v.m_Pos.x;
			else if (max.x < v.m_Pos.x) max.x = v.m_Pos.x;

			if (min.y > v.m_Pos.y)	min.y = v.m_Pos.y;
			else if (max.y < v.m_Pos.y) max.y = v.m_Pos.y;

			if (min.z > v.m_Pos.z)	min.z = v.m_Pos.z;
			else if (max.z < v.m_Pos.z) max.z = v.m_Pos.z;
		}
	}
}
