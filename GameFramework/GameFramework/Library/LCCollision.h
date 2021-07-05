#pragma once
#include <DirectXMath.h>
#include <vector>
#include "../ExternalCode/Mesh.h"

using namespace DirectX;

static class LCCollision
{
public:

	//AABB     Intersect:�����@�@�@�@Contains:����
	static bool Intersect(const XMFLOAT3& AMin, const XMFLOAT3& AMax, const XMFLOAT3& BMin, const XMFLOAT3& BMax);
	static bool Contains(const XMFLOAT3& AMin, const XMFLOAT3& AMax, const XMFLOAT3& point);
	//Sphere   Intersect:����
	static bool Intersect(const XMFLOAT3& ACenter,const float& ARadius, const XMFLOAT3& BCenter, const float& BRadius);

	//���_���b�V���̍ő�ŏ������o��
	static void CalcMinMaxOfMeshes(const std::vector<Mesh>& meshes, XMFLOAT3& min, XMFLOAT3& max);
};
