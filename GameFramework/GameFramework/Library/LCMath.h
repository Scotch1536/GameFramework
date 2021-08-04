#pragma once
#include <DirectXMath.h>

using namespace DirectX;

static class LCMath
{
public:
	//オイラー角からクォータニオンに変換
	static const XMFLOAT4& TransformFromEulerAnglesToQuaternion(const XMFLOAT3& axisX , const XMFLOAT3& axisY , const XMFLOAT3& axisZ ,
		const XMFLOAT3& eulerAngle , XMFLOAT4& resultQua);

	//クォータニオンからオイラー角に変換
	static const XMFLOAT3& TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua , XMFLOAT3& resultAngle);

	//単位行列化
	static void IdentityMatrix(XMFLOAT4X4& target);

	//ロケーション、スケール、回転行列から指定の行列を更新
	static const XMFLOAT4X4& UpdateMatrix(const XMFLOAT3& location , const XMFLOAT3& scale , const XMFLOAT4X4& rotMTX , XMFLOAT4X4& resultMTX);

	//逆行列を取得
	static const XMFLOAT4X4& InverseMatrix(const XMFLOAT4X4& target , XMFLOAT4X4& resultMTX);


	//指定のFloat3同士が一致しているかの比較
	static bool CompareFloat3(const XMFLOAT3& target1 , const XMFLOAT3& target2);

	//指定の行列同士が一致しているかの比較
	static bool CompareMatrix(const XMFLOAT4X4& target1 , const XMFLOAT4X4& target2);

	//軸（向きベクトル）と角度(ラジアン)からクォータニオンを作成	
	static const XMFLOAT4& CreateFromAxisAndAngleToQuaternion(const XMFLOAT3& axis , const float& angle , XMFLOAT4& resultQua);

	static const XMFLOAT4& CalcQuaternionToLocation(const XMFLOAT3& currentLocation , const XMFLOAT3& currentOrienVec , const XMFLOAT3& location , XMFLOAT4& resultQua);

	static const XMFLOAT4& CalcQuaternionMultiply(const XMFLOAT4& qua1 , const XMFLOAT4& qua2 , XMFLOAT4& result);

	//スタートからゴールへのベクトルをゲット
	static const XMFLOAT3& CalcFloat3FromStartToGoal(const XMFLOAT3& start , const XMFLOAT3& goal , XMFLOAT3& resultVec);

	static const float& CalcFloat3Length(const XMFLOAT3& target , float& resultLen);

	static const XMFLOAT3& CalcFloat3Normalize(const XMFLOAT3& target , XMFLOAT3& resultVec);

	static const float& CalcFloat3Dot(const XMFLOAT3& target1 , const XMFLOAT3& target2 , float& resultScaler);

	static const XMFLOAT3& CalcFloat3Cross(const XMFLOAT3& target1 , const XMFLOAT3& target2 , XMFLOAT3& resultVec);

	//線形補間
	static const float& Lerp(const float& start , const float& end , const float& alpha , float& result);
	static const XMFLOAT3& Lerp(const XMFLOAT3& start , const XMFLOAT3& end , const float& alpha , XMFLOAT3& result);
	static const XMFLOAT4& Lerp(const XMFLOAT4& start , const XMFLOAT4& end , const float& alpha , XMFLOAT4& result);
};