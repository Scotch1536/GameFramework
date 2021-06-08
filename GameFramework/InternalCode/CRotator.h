#pragma once
#include "dx11mathutil.h"
#include <memory>

class CRotator
{
private:
	float mAlpha;
	float mInc;

	XMFLOAT3 mAngle;	//角度（度数法）
	XMFLOAT4X4 mMtx;	//マトリックス
	XMFLOAT4 mQua;		//クォータニオン（現在地）
	std::unique_ptr<XMFLOAT4> mStartQua;	//クォータニオン（移動前）
	std::unique_ptr<XMFLOAT4> mGoalQua;		//クォータニオン（移動後）
	
public :
	CRotator() {};

	//初期化
	void Init();

	//更新
	void Update();

	//角度セット
	void SetAngle(XMFLOAT3 angle ,float time);

	//マトリックス取得
	XMFLOAT4X4 GetMtx();

	//オイラー角からクォータニオンに変換
	void EulerAnglesToQuaternion(XMFLOAT3 angle, XMFLOAT4 qua);
};