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

	//XMFLOAT4X4 mMatrix;			//マトリックス

	std::unique_ptr<XMFLOAT4> mFromQuaternion;			//クォータニオン（移動前）
	std::unique_ptr<XMFLOAT4> mToQuaternion;			//クォータニオン（移動後）
	
	//オイラー角からクォータニオンに変換
	void TransformFromEulerAnglesToQuaternion(const XMFLOAT3& angle, XMFLOAT4& qua);

	//クォータニオンからオイラー角に変換
	void TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua , XMFLOAT3& angle);
public :
	CRotator();

	////初期化
	//void Init();

	//更新
	void Update();

	//角度セット
	void SetAngle(XMFLOAT3 angle /*,float time*/);

	void RequestSLerp(XMFLOAT3 angle , float time);

	//マトリックス取得
	XMFLOAT4X4 GenerateMatrix(CTransform& partner);
};