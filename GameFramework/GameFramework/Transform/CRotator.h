#pragma once
#include <memory>
#include <DirectXMath.h>

using namespace DirectX;

class CTransform;
class CChildTransform;

//ローテータークラス
class CRotator
{
private:
	XMFLOAT4 mQuaternion;							//クォータニオン（現在地）
	XMFLOAT3 mLastFrameAngle = { 0.f,0.f,0.f };		//比較するための角度

	bool mIsSameAngle = true;		//比較結果（今のフレームの角度と前のフレーム角度の）

public:
	XMFLOAT3 Angle = { 0.f,0.f,0.f };			//角度（度数法）

	CRotator();

	//更新
	bool Update();

	//マトリックス取得
	XMFLOAT4X4 GenerateMatrix(CTransform& partner);

	const XMFLOAT4& GetQuaternion()const
	{
		return mQuaternion;
	}

	const bool& GetIsSameAngle()const
	{
		return mIsSameAngle;
	}

	void SetQuaternion(CChildTransform& partner , XMFLOAT4& qua)
	{
		mQuaternion = qua;
	}
};