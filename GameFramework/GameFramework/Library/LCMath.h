#pragma once
#include <DirectXMath.h>

using namespace DirectX;

static class LCMath
{
public:
	//オイラー角からクォータニオンに変換
	static void TransformFromEulerAnglesToQuaternion(const XMFLOAT3& angle , XMFLOAT4& ansQua);

	//クォータニオンからオイラー角に変換
	//static void TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua , XMFLOAT3& angle);

	//ロケーション、スケール、回転行列から指定の行列を更新
	static void UpdateMatrix(const XMFLOAT3& location , const XMFLOAT3& scale , const XMFLOAT4X4& rotMTX , XMFLOAT4X4& result);

	//指定のFloat3同士が一致しているかの比較
	static bool CompareFloat3(const XMFLOAT3& target1 , const XMFLOAT3& target2);

	//指定の行列同士が一致しているかの比較
	static bool CompareMatrix(const XMFLOAT4X4& target1 , const XMFLOAT4X4& target2);

	//スタートからゴールへのベクトルをゲット
	static void CalcFloat3FromStartToGoal(const XMFLOAT3& start , const XMFLOAT3& goal , XMFLOAT3& ansVec);

	static void CalcFloat3Length(const XMFLOAT3& target , float& ansLength);

	static void CalcFloat3Normalize(const XMFLOAT3& target , XMFLOAT3& ansvec);

	//線形補間
	static float Lerp(float start , float end , float alpha);
	static XMFLOAT3 Lerp(const XMFLOAT3& start , const XMFLOAT3& end , float alpha);
};