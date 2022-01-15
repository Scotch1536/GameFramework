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
	CTransform& mPartner;

	XMFLOAT4 mQuaternion;				//クォータニオン（現在地）
	XMFLOAT4 mLastFrameQuaternion;		//1フレーム前のクォータニオン

	bool mIsSameQuaternionToBeforeFrame = true;			//比較結果（今のフレームの角度と前のフレーム角度の）

public:
	CRotator(CTransform& partner);

	//更新
	bool Update();

	//マトリックス取得
	XMFLOAT4X4 GenerateMatrix();

	//指定の位置に角度を変更する
	void ChangeQuaternionToLocation(XMFLOAT3 location);

	//指定の位置に向くクォータニオンをゲットする
	void CalcQuaternionToLocation(XMFLOAT3 location , XMFLOAT4& resultQua);

	const XMFLOAT4& GetQuaternion()const
	{
		return mQuaternion;
	}

	const bool& GetIsSameQuaternionToBeforeFrame()const
	{
		return mIsSameQuaternionToBeforeFrame;
	}

	void SetQuaternion(const XMFLOAT4& qua)
	{
		mQuaternion = qua;
	}

	void SetAngle(const XMFLOAT3& angle);

	void AddAngleRelative(const XMFLOAT3& angle);

	void AddAngleWorld(const XMFLOAT3& angle);

};