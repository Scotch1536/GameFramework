//!
//!	@file
//!	@brief コリジョンライブラリのソースファイル
//!

#include <algorithm>

#include "LCCollision.h"

bool LCCollision::IsCollide(const XMFLOAT3& min1 , const XMFLOAT3& max1 , const XMFLOAT3& min2 , const XMFLOAT3& max2)
{
	if(max1.x < min2.x ||
		max1.y < min2.y ||
		max1.z < min2.z ||
		max2.x < min1.x ||
		max2.y < min1.y ||
		max2.z < min1.z)
	{
		return false;
	}
	return true;
}

bool LCCollision::IsCollide(const XMFLOAT3& min , const XMFLOAT3& max , const XMFLOAT3& point)
{
	if(point.x < min.x ||
		point.y < min.y ||
		point.z < min.z ||
		point.x > max.x ||
		point.y > max.y ||
		point.z > max.z)
	{
		return false;
	}
	return true;
}

bool LCCollision::IsCollide(const XMFLOAT3& center1 , const float& radius1 , const XMFLOAT3& center2 , const float& radius2)
{
	float dx = center1.x - center2.x;
	float dy = center1.y - center2.y;
	float dz = center1.z - center2.z;

	float radius = radius1 + radius2;

	return (dx * dx) + (dy * dy) + (dz * dz) <= (radius * radius);
}

bool LCCollision::IsCollide(const XMFLOAT3& min , const XMFLOAT3& max , const XMFLOAT3& center , const float& radius)
{
	//軸の差を算出
	float dx = (std::max)(min.x - center.x , 0.0f);
	dx = (std::max)(dx , center.x - max.x);
	float dy = (std::max)(min.y - center.y , 0.0f);
	dy = (std::max)(dy , center.y - max.y);
	float dz = (std::max)(min.z - center.z , 0.0f);
	dz = (std::max)(dz , center.z - max.z);

	float dist = dx * dx + dy * dy + dz * dz;

	return dist <= (radius * radius);
}
