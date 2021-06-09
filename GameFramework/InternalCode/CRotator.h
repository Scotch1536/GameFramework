#pragma once
#include <memory>
#include "dx11mathutil.h"

class CTransform;

class CRotator
{
private:
	float mAlpha;					//Slerpで使用するアルファ値
	float mIncreaceAlpha;			//アルファの増加値

	XMFLOAT3 mAngle;				//角度（度数法）
	XMFLOAT4 mQuaternion;			//クォータニオン（現在地）

	std::unique_ptr<XMFLOAT4> mFromQuaternion;			//クォータニオン（移動前）
	std::unique_ptr<XMFLOAT4> mToQuaternion;			//クォータニオン（移動後）
	
	//オイラー角からクォータニオンに変換
	void TransformFromEulerAnglesToQuaternion(const XMFLOAT3& angle, XMFLOAT4& qua);

	//クォータニオンからオイラー角に変換
	void TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua , XMFLOAT3& angle);
public :
	CRotator();

	//更新
	void Update();

	//球面線形補間をリクエスト
	void RequestSLerp(XMFLOAT3 angle , float lerpTime);

	//マトリックス取得
	XMFLOAT4X4 GenerateMatrix(CTransform& partner);

	//角度セット
	void SetAngle(XMFLOAT3 angle);

	const XMFLOAT3& GetAngle()const
	{
		return mAngle;
	}
};