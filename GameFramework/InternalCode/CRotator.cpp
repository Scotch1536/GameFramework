#include "CRotator.h"
#include "CTransform.h"

CRotator::CRotator()
{
	DX11QtIdentity(mQuaternion);
}

void CRotator::Update()
{
	if(mToQuaternion != nullptr)
	{
		DX11QtSlerp(*mFromQuaternion , *mToQuaternion , mAlpha , mQuaternion);

		TransformFromQuaternionToEulerAngles(mQuaternion , mAngle);

		if(mAlpha >= 1.0f)
		{
			mFromQuaternion.reset();
			mToQuaternion.reset();
		}
		mAlpha += mIncreaceAlpha;
	}
}

void CRotator::SetAngle(XMFLOAT3 angle)
{
	mAngle = angle;

	TransformFromEulerAnglesToQuaternion(mAngle , mQuaternion);
}

void CRotator::RequestSLerp(XMFLOAT3 angle , float time)
{
	if(mAlpha != 0.f)mAlpha = 0.f;
	mIncreaceAlpha = 1 / (time * 60);

	mFromQuaternion.reset(new XMFLOAT4);
	mToQuaternion.reset(new XMFLOAT4);

	*mFromQuaternion = mQuaternion;

	TransformFromEulerAnglesToQuaternion(mAngle , *mToQuaternion);
}

XMFLOAT4X4 CRotator::GenerateMatrix(CTransform& partner)
{
	XMFLOAT4X4 ansMTX;

	//クォータニオンから行列を作成
	DX11MtxFromQt(ansMTX , mQuaternion);

	return ansMTX;
}

void CRotator::TransformFromEulerAnglesToQuaternion(const XMFLOAT3& angle , XMFLOAT4& qua)
{
	float cosRoll = cos(angle.x / 2.0f);
	float sinRoll = sin(angle.x / 2.0f);
	float cosPitch = cos(angle.y / 2.0f);
	float sinPitch = sin(angle.y / 2.0f);
	float cosYaw = cos(angle.z / 2.0f);
	float sinYaw = sin(angle.z / 2.0f);

	qua.x = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;
	qua.y = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
	qua.z = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
	qua.w = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;
}

void CRotator::TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua , XMFLOAT3& angle)
{
	float q0q0 = qua.x * qua.x;
	float q0q1 = qua.x * qua.y;
	float q0q2 = qua.x * qua.z;
	float q0q3 = qua.x * qua.w;
	float q1q1 = qua.y * qua.y;
	float q1q2 = qua.y * qua.z;
	float q1q3 = qua.y * qua.w;
	float q2q2 = qua.z * qua.z;
	float q2q3 = qua.z * qua.w;
	float q3q3 = qua.w * qua.w;

	angle.x = atan2(2.0 * (q2q3 + q0q1) , q0q0 - q1q1 - q2q2 + q3q3);
	angle.y = asin(2.0 * (q0q2 - q1q3));
	angle.z = atan2(2.0 * (q1q2 + q0q3) , q0q0 + q1q1 - q2q2 - q3q3);
}