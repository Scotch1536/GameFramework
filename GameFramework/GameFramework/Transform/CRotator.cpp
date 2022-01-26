#include "../Library/LCMath.h"

#include "CRotator.h"
#include "CTransform.h"

CRotator::CRotator(CTransform& partner):mPartner(partner)
{
	LCMath::IdentityQuaternion(mQuaternion);
	LCMath::IdentityQuaternion(mLastFrameQuaternion);
}

//void CRotator::UpdateAngle(float& angle)
//{
//	if(angle < 0.0f)
//	{
//		angle = 360.0f + angle;
//	}
//	else if(angle > 360.0f)
//	{
//		angle = angle - 360.0f;
//	}
//}

bool CRotator::Update()
{
	if(!LCMath::CompareFloat4(mQuaternion , mLastFrameQuaternion))
	{
		mLastFrameQuaternion = mQuaternion;

		mIsSameQuaternionToBeforeFrame = false;
	}
	else
	{
		mIsSameQuaternionToBeforeFrame = true;
	}
	return false;
}

XMFLOAT4X4 CRotator::GenerateMatrix()
{
	XMFLOAT4X4 ansMTX;

	//クォータニオンから行列を作成
	LCMath::CalcMatrixFromQuaternion(mQuaternion , ansMTX);

	return ansMTX;
}

void CRotator::SetAngle(const XMFLOAT3& angle)
{
	LCMath::TransformFromEulerAnglesToQuaternion({ 1.0f,0.0f,0.0f } , { 0.0f , 1.0f , 0.0f } ,
		{ 0.0f,0.0f,1.0f } , angle , mQuaternion);

	mPartner.Update();
}

void CRotator::AddAngleRelative(const XMFLOAT3& angle)
{
	XMFLOAT4 qua;

	LCMath::TransformFromEulerAnglesToQuaternion(mPartner.GetRightVectorRelative() , mPartner.GetUpwardVectorRelative() ,
		mPartner.GetForwardVectorRelative() , angle , qua);
	LCMath::CalcQuaternionMultiply(mQuaternion , qua , mQuaternion);

	mPartner.Update();
}

void CRotator::AddAngleWorld(const XMFLOAT3& angle)
{
	XMFLOAT4 qua;

	LCMath::TransformFromEulerAnglesToQuaternion(mPartner.GetRightVectorWorld() , mPartner.GetUpwardVectorWorld() ,
		mPartner.GetForwardVectorWorld() , angle , qua);
	LCMath::CalcQuaternionMultiply(mQuaternion , qua , mQuaternion);

	mPartner.Update();
}

void CRotator::ChangeQuaternionToLocation(XMFLOAT3 location)
{
	XMFLOAT4 mulQua;
	XMFLOAT3 vec , axis;
	float angle;

	//向きたい位置へのベクトルを算出
	LCMath::CalcFloat3FromStartToGoal(mPartner.Location , location , vec);

	//向きベクトルにするために正規化
	LCMath::CalcFloat3Normalize(vec , vec);

	//クォータニオンに必要な角度を算出
	LCMath::CalcFloat3Dot(mPartner.GetForwardVectorWorld() , vec , angle);

	/*
	結果が1(小数点がはみ出ることがあるので1以上)ならベクトル同士が平行なので終了
	-1以下なら-1にする
	*/
	if(angle >= 1.0f)return;
	else if(angle < -1.0f)angle = -1.0f;

	//角度を求める
	angle = std::acosf(angle);

	//クォータニオンに必要な軸を算出
	LCMath::CalcFloat3Cross(mPartner.GetForwardVectorWorld() , vec , axis);

	//軸が全て0なら軸を自分の上向きベクトルにする
	if(axis.x == 0 && axis.y == 0 && axis.z == 0)
	{
		axis = mPartner.GetUpwardVectorWorld();
	};

	//クォータニオン作成
	LCMath::CreateFromAxisAndAngleToQuaternion(axis , angle , mulQua);

	//クォータニオンの合成
	LCMath::CalcQuaternionMultiply(mQuaternion , mulQua , mQuaternion);
}

void CRotator::CalcQuaternionToLocation(XMFLOAT3 location , XMFLOAT4& resultQua)
{
	XMFLOAT4 mulQua;
	XMFLOAT3 vec , axis;
	float angle;

	//向きたい位置へのベクトルを算出
	LCMath::CalcFloat3FromStartToGoal(mPartner.GetWorldLocation() , location , vec);

	//向きベクトルにするために正規化
	LCMath::CalcFloat3Normalize(vec , vec);

	//クォータニオンに必要な角度を算出
	LCMath::CalcFloat3Dot(mPartner.GetForwardVectorWorld() , vec , angle);

	/*
	結果が1(小数点がはみ出ることがあるので1以上)ならベクトル同士が平行なので終了
	-1以下なら-1にする
	*/
	if(angle >= 1.0f)
	{
		LCMath::IdentityQuaternion(resultQua);

		return;
	}
	else if(angle < -1.0f)angle = -1.0f;

	//角度を求める
	angle = std::acosf(angle);

	//クォータニオンに必要な軸を算出
	LCMath::CalcFloat3Cross(mPartner.GetForwardVectorWorld() , vec , axis);

	//軸が全て0なら軸を自分の上向きベクトルにする
	if(axis.x == 0 && axis.y == 0 && axis.z == 0)
	{
		axis = mPartner.GetUpwardVectorWorld();
	};

	//クォータニオン作成
	LCMath::CreateFromAxisAndAngleToQuaternion(axis , angle , mulQua);

	//クォータニオンの合成
	LCMath::CalcQuaternionMultiply(mQuaternion , mulQua , resultQua);
}