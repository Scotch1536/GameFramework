#pragma once
#include <DirectXMath.h>
#include <vector>

#include "../Data/CMeshData.h"

using namespace DirectX;

static class LCCollision
{
public:

	//AABB     Intersect:交差　　　　Contains:内包
	static bool Intersect(const XMFLOAT3& AMin, const XMFLOAT3& AMax, const XMFLOAT3& BMin, const XMFLOAT3& BMax);
	static bool Contains(const XMFLOAT3& AMin, const XMFLOAT3& AMax, const XMFLOAT3& point);
	//Sphere   Intersect:交差
	static bool Intersect(const XMFLOAT3& ACenter,const float& ARadius, const XMFLOAT3& BCenter, const float& BRadius);

	//頂点メッシュの最大最小を取り出す
	static void CalcMinMaxOfMeshes(const std::vector<CMeshData>& meshes, XMFLOAT3& min, XMFLOAT3& max);
};
