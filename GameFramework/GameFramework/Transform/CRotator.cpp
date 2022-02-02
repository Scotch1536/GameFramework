//!
//!	@file
//!	@brief ローテーターシステムのソースファイル
//!

#include "../Library/LCMath.h"

#include "CRotator.h"
#include "CTransform.h"

CRotator::CRotator(CTransform& partner):mPartner(partner)
{
	LCMath::IdentityQuaternion(mQuaternion);
	LCMath::IdentityQuaternion(mLastFrameQuaternion);
}

void CRotator::Update()
{
	//一致しなければ
	if(!LCMath::CompareFloat4(mQuaternion , mLastFrameQuaternion))
	{
		mLastFrameQuaternion = mQuaternion;

		mIsSameQuaternionToBeforeFrame = false;
	}
	else
	{
		mIsSameQuaternionToBeforeFrame = true;
	}
}

XMFLOAT4X4 CRotator::GenerateMatrix()
{
	XMFLOAT4X4 ansMTX;

	//クォータニオンから行列を作成
	LCMath::TransformFromQuaternionToMatrix(mQuaternion , ansMTX);

	return ansMTX;
}

void CRotator::SetAngle(const XMFLOAT3& angle)
{
	LCMath::TransformFromEulerAnglesToQuaternion({ 1.0f,0.0f,0.0f } , { 0.0f , 1.0f , 0.0f } ,
		{ 0.0f,0.0f,1.0f } , angle , mQuaternion);

	mPartner.Update();
}

void CRotator::AddAngleLocal(const XMFLOAT3& angle)
{
	XMFLOAT4 qua;

	//ローカルの姿勢を回転軸にクォータニオンを算出
	LCMath::TransformFromEulerAnglesToQuaternion(mPartner.GetLocalRightVector() , mPartner.GetLocalUpwardVector() ,
		mPartner.GetLocalForwardVector() , angle , qua);

	//クォータニオンの合成
	LCMath::CalcQuaternionMultiply(mQuaternion , qua , mQuaternion);

	mPartner.Update();
}

void CRotator::AddAngleWorld(const XMFLOAT3& angle)
{
	XMFLOAT4 qua;

	//ワールドの姿勢を回転軸にクォータニオンを算出
	LCMath::TransformFromEulerAnglesToQuaternion(mPartner.GetWorldRightVector() , mPartner.GetWorldUpwardVector() ,
		mPartner.GetWorldForwardVector() , angle , qua);

	//クォータニオンの合成
	LCMath::CalcQuaternionMultiply(mQuaternion , qua , mQuaternion);

	mPartner.Update();
}

void CRotator::ChangeQuaternionToLocation(XMFLOAT3 location)
{
	XMFLOAT4 mulQua;
	XMFLOAT3 vec , axis;
	float angle;

	//向きたい位置へのベクトルを算出
	LCMath::CalcFloat3FromStartToEnd(mPartner.Location , location , vec);

	//向きベクトルにするために正規化
	LCMath::CalcFloat3Normalize(vec , vec);

	//クォータニオンに必要な角度を算出
	LCMath::CalcFloat3Dot(mPartner.GetWorldForwardVector() , vec , angle);

	/*
	結果が1(小数点がはみ出ることがあるので1以上)ならベクトル同士が平行なので終了
	-1以下なら-1にする
	*/
	if(angle >= 1.0f)return;
	else if(angle < -1.0f)angle = -1.0f;

	//角度を求める
	angle = std::acosf(angle);

	//クォータニオンに必要な軸を算出
	LCMath::CalcFloat3Cross(mPartner.GetWorldForwardVector() , vec , axis);

	//軸が全て0なら軸を自分の上向きベクトルにする
	if(axis.x == 0 && axis.y == 0 && axis.z == 0)
	{
		axis = mPartner.GetWorldUpwardVector();
	};

	//クォータニオン作成
	LCMath::CreateFromAxisAndAngleToQuaternion(axis , angle , mulQua);

	//クォータニオンの合成
	LCMath::CalcQuaternionMultiply(mQuaternion , mulQua , mQuaternion);
}

void CRotator::CalcQuaternionToLocation(XMFLOAT3 location , XMFLOAT4& result)
{
	XMFLOAT4 mulQua;
	XMFLOAT3 vec , axis;
	float angle;

	//向きたい位置へのベクトルを算出
	LCMath::CalcFloat3FromStartToEnd(mPartner.GetWorldLocation() , location , vec);

	//向きベクトルにするために正規化
	LCMath::CalcFloat3Normalize(vec , vec);

	//クォータニオンに必要な角度を算出
	LCMath::CalcFloat3Dot(mPartner.GetWorldForwardVector() , vec , angle);

	/*
	結果が1(小数点がはみ出ることがあるので1以上)ならベクトル同士が平行なので終了
	-1以下なら-1にする
	*/
	if(angle >= 1.0f)
	{
		LCMath::IdentityQuaternion(result);

		return;
	}
	else if(angle < -1.0f)angle = -1.0f;

	//角度を求める
	angle = std::acosf(angle);

	//クォータニオンに必要な軸を算出
	LCMath::CalcFloat3Cross(mPartner.GetWorldForwardVector() , vec , axis);

	//軸が全て0なら軸を自分の上向きベクトルにする
	if(axis.x == 0 && axis.y == 0 && axis.z == 0)
	{
		axis = mPartner.GetWorldUpwardVector();
	};

	//クォータニオン作成
	LCMath::CreateFromAxisAndAngleToQuaternion(axis , angle , mulQua);

	//クォータニオンの合成
	LCMath::CalcQuaternionMultiply(mQuaternion , mulQua , result);
}