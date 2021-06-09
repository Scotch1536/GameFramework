#pragma once
#include <DirectXMath.h>

using namespace DirectX;

static class LCMath
{
public:
	static void TransformFromEulerAnglesToQuaternion(const XMFLOAT3& angle , XMFLOAT4& qua);

	static void TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua , XMFLOAT3& angle);

	static void UpdateMatrix(const XMFLOAT3& location , const XMFLOAT3& scale , XMFLOAT4X4 rotMTX , XMFLOAT4X4& result);

	static bool CompareFloat3(const XMFLOAT3& target1 , const XMFLOAT3& target2);
};