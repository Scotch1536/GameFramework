#pragma once
#include <DirectXMath.h>

using namespace DirectX;

static class LCMath
{
public:
	//オイラー角からクォータニオンに変換
	static void TransformFromEulerAnglesToQuaternion(const XMFLOAT3& angle , XMFLOAT4& qua);

	//クォータニオンからオイラー角に変換
	static void TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua , XMFLOAT3& angle);

	//ロケーション、スケール、回転行列から指定の行列を更新
	static void UpdateMatrix(const XMFLOAT3& location , const XMFLOAT3& scale , XMFLOAT4X4 rotMTX , XMFLOAT4X4& result);

	//指定のFloat3同士が一致しているかの比較
	static bool CompareFloat3(const XMFLOAT3& target1 , const XMFLOAT3& target2);

	//線形補間
	static float Lerp(float start , float end , float alpha);
};