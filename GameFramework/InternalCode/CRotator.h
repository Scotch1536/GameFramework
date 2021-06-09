#pragma once
#include <memory>
#include <DirectXMath.h>

using namespace DirectX;

class CTransform;
class CChildTransform;

class CRotator
{
private:
	float mAlpha;					//Slerpで使用するアルファ値
	float mIncreaceAlpha;			//アルファの増加値

	XMFLOAT4 mQuaternion;							//クォータニオン（現在地）
	XMFLOAT3 mCompareAngle = { 0.f,0.f,0.f };		//比較するための角度

	std::unique_ptr<XMFLOAT4> mFromQuaternion;			//クォータニオン（移動前）
	std::unique_ptr<XMFLOAT4> mToQuaternion;			//クォータニオン（移動後）

	bool mIsNowFrameCompareResult = true;
	//bool mIsLastUpdate = false;
public:
	XMFLOAT3 angle = { 0.f,0.f,0.f };			//角度（度数法）

	CRotator();

	//更新
	bool Update();

	////球面線形補間をリクエスト
	//void RequestSLerp(XMFLOAT3 angle , float lerpTime);

	//マトリックス取得
	XMFLOAT4X4 GenerateMatrix(CTransform& partner);

	const XMFLOAT4& GetQuaternion()const
	{
		return mQuaternion;
	}

	const bool& GetIsNowCompareResult()const
	{
		return mIsNowFrameCompareResult;
	}

	void SetQuaternion(CChildTransform& partner , XMFLOAT4& qua)
	{
		mQuaternion = qua;
	}
};