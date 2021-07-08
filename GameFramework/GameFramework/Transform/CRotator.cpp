#include "../Library/LCMath.h"
#include "../ExternalCode/dx11mathutil.h"

#include "CRotator.h"
#include "CTransform.h"

CRotator::CRotator(const CTransform& partner):mPartner(partner)
{
	DX11QtIdentity(mQuaternion);
}

bool CRotator::Update()
{
	if(!LCMath::CompareFloat3(mAngle , mLastFrameAngle))
	{
		mLastFrameAngle = mAngle;

		mIsSameAngle = false;
	}
	else
	{
		mIsSameAngle = true;
	}
	return false;
}

XMFLOAT4X4 CRotator::GenerateMatrix()
{
	XMFLOAT4X4 ansMTX;

	//クォータニオンから行列を作成
	DX11MtxFromQt(ansMTX , mQuaternion);

	return ansMTX;
}

void CRotator::SetAngle(const XMFLOAT3& angle)
{
	mAngle = angle;

	LCMath::TransformFromEulerAnglesToQuaternion(mPartner.GetRightVector() , mPartner.GetUpwardVector() ,
		mPartner.GetForwardVector() , mAngle , mQuaternion);
}

void CRotator::AddAngle(const XMFLOAT3& angle)
{
	XMFLOAT4 qua;

	mAngle.x += angle.x;
	mAngle.y += angle.y;
	mAngle.z += angle.z;

	LCMath::TransformFromEulerAnglesToQuaternion(mPartner.GetRightVector() , mPartner.GetUpwardVector() ,
		mPartner.GetForwardVector() , angle , qua);
	LCMath::CalcQuaternionMultiply(mQuaternion , qua , mQuaternion);
}

void CRotator::ChangeAngleToLocation(XMFLOAT3 location)
{
	XMFLOAT4 mulQua;
	XMFLOAT3 vec , axis , eulerAngles;
	float angle;

	//向きたい位置へのベクトルを計算
	LCMath::CalcFloat3FromStartToGoal(mPartner.Location , location , vec);

	//向きベクトルにするために正規化
	LCMath::CalcFloat3Normalize(vec , vec);

	//クォータニオンに必要な角度を計算
	angle = acosf(LCMath::CalcFloat3Dot(mPartner.GetForwardVector() , vec , angle));
	angle = XMConvertToDegrees(angle);

	//角度が0なら終了
	if(angle == 0)return;

	//クォータニオンに必要な軸を計算
	LCMath::CalcFloat3Cross(mPartner.GetForwardVector() , vec , axis);

	//軸が全て0なら終了
	if(axis.x == 0 && axis.y == 0 && axis.z == 0)return;

	//クォータニオン作成
	LCMath::CreateFromAxisAndAngleToQuaternion(axis , angle , mulQua);

	//クォータニオンの合成
	LCMath::CalcQuaternionMultiply(mQuaternion , mulQua , mQuaternion);

	//クォータニオンをオイラー角に変換
	LCMath::TransformFromQuaternionToEulerAngles(mQuaternion , eulerAngles);

	//角度をセット
	mAngle = eulerAngles;
}