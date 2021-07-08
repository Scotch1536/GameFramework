#pragma once
#include <memory>
#include <DirectXMath.h>

#include "../Library/LCMath.h"

using namespace DirectX;

class CTransform;

//ローテータークラス
class CRotator
{
private:
	const CTransform& mPartner;

	XMFLOAT4 mQuaternion;		//クォータニオン（現在地）

	XMFLOAT3 mAngle = { 0.f,0.f,0.f };				//角度（度数法）
	XMFLOAT3 mLastFrameAngle = { 0.f,0.f,0.f };		//1フレーム前の角度（度数法）

	bool mIsSameAngle = true;				//比較結果（今のフレームの角度と前のフレーム角度の）

	void UpdateAngle(float& angle);

public:
	CRotator(const CTransform& partner);

	//更新
	bool Update();

	//マトリックス取得
	XMFLOAT4X4 GenerateMatrix();

	//指定の位置に角度を変更する
	void ChangeAngleToLocation(XMFLOAT3 location);

	const XMFLOAT4& GetQuaternion()const
	{
		return mQuaternion;
	}

	const XMFLOAT3& GetAngle()const
	{
		return mAngle;
	}

	const bool& GetIsSameAngle()const
	{
		return mIsSameAngle;
	}

	void SetQuaternion(const XMFLOAT4& qua)
	{
		mQuaternion = qua;
	}

	void SetAngle(const XMFLOAT3& angle);

	void AddAngle(const XMFLOAT3& angle);

};