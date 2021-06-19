#include "LCMath.h"

void LCMath::TransformFromEulerAnglesToQuaternion(const XMFLOAT3& angle , XMFLOAT4& qua)
{
	float x = XMConvertToRadians(angle.x);
	float y = XMConvertToRadians(angle.y);
	float z = XMConvertToRadians(angle.z);

	float cosRoll = cos(x / 2.0f);
	float sinRoll = sin(x / 2.0f);
	float cosPitch = cos(y / 2.0f);
	float sinPitch = sin(y / 2.0f);
	float cosYaw = cos(z / 2.0f);
	float sinYaw = sin(z / 2.0f);

	qua.x = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;
	qua.y = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
	qua.z = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
	qua.w = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;
}

void LCMath::TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua , XMFLOAT3& angle)
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

	float x = atan2(2.0 * (q2q3 + q0q1) , q0q0 - q1q1 - q2q2 + q3q3);
	float y = asin(2.0 * (q0q2 - q1q3));
	float z = atan2(2.0 * (q1q2 + q0q3) , q0q0 + q1q1 - q2q2 - q3q3);

	angle.x = floorf(XMConvertToDegrees(x));
	angle.y = floorf(XMConvertToDegrees(y));
	angle.z = floorf(XMConvertToDegrees(z));
}

void LCMath::UpdateMatrix(const XMFLOAT3& location , const XMFLOAT3& scale , XMFLOAT4X4 rotMTX , XMFLOAT4X4& result)
{
	result._11 = scale.x * rotMTX._11;
	result._12 = scale.y * rotMTX._12;
	result._13 = scale.z * rotMTX._13;

	result._21 = scale.x * rotMTX._21;
	result._22 = scale.y * rotMTX._22;
	result._23 = scale.z * rotMTX._23;

	result._31 = scale.x * rotMTX._31;
	result._32 = scale.y * rotMTX._32;
	result._33 = scale.z * rotMTX._33;

	result._41 = location.x;
	result._42 = location.y;
	result._43 = location.z;
	result._44 = 1;
}

bool LCMath::CompareFloat3(const XMFLOAT3& target1 , const XMFLOAT3& target2)
{
	if(target1.x != target2.x)return false;
	if(target1.y != target2.y)return false;
	if(target1.z != target2.z)return false;
	return true;
}

float LCMath::Lerp(float start , float end , float alpha)
{
	return (1 - alpha)*start + alpha * end;
}