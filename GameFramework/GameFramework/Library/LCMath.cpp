#include "LCMath.h"

#include "../ExternalCode/dx11mathutil.h"

void LCMath::TransformFromEulerAnglesToQuaternion(const XMFLOAT3& angle , XMFLOAT4& ansQua)
{
	XMFLOAT4 qtx , qty , qtz;
	XMFLOAT4 axisX = { 1,0,0,0 };
	XMFLOAT4 axisY = { 0,1,0,0 };
	XMFLOAT4 axisZ = { 0,0,1,0 };

	DX11QtRotationAxis(qtx , axisX , angle.x);
	DX11QtRotationAxis(qty , axisY , angle.y);
	DX11QtRotationAxis(qtz , axisZ , angle.z);

	DX11QtMul(ansQua , qtx , qty);
	DX11QtMul(ansQua , ansQua , qtz);
}

void LCMath::UpdateMatrix(const XMFLOAT3& location , const XMFLOAT3& scale , const XMFLOAT4X4& rotMTX , XMFLOAT4X4& result)
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

bool LCMath::CompareMatrix(const XMFLOAT4X4& target1 , const XMFLOAT4X4& target2)
{
	if(target1._11 != target2._11)return false;
	if(target1._12 != target2._12)return false;
	if(target1._13 != target2._13)return false;
	if(target1._14 != target2._14)return false;

	if(target1._21 != target2._21)return false;
	if(target1._22 != target2._22)return false;
	if(target1._23 != target2._23)return false;
	if(target1._24 != target2._24)return false;

	if(target1._31 != target2._31)return false;
	if(target1._32 != target2._32)return false;
	if(target1._33 != target2._33)return false;
	if(target1._34 != target2._34)return false;

	if(target1._41 != target2._41)return false;
	if(target1._42 != target2._42)return false;
	if(target1._43 != target2._43)return false;
	if(target1._44 != target2._44)return false;

	return true;
}

void LCMath::CalcFloat3FromStartToGoal(const XMFLOAT3& start , const XMFLOAT3& goal , XMFLOAT3& ansVec)
{
	XMVECTOR startVec = XMLoadFloat3(&start);
	XMVECTOR goalVec = XMLoadFloat3(&goal);

	XMStoreFloat3(&ansVec , XMVectorSubtract(goalVec , startVec));
}

void LCMath::CalcFloat3Length(const XMFLOAT3& target , float& ansLength)
{
	DX11Vec3Length(target , ansLength);
}

void LCMath::CalcFloat3Normalize(const XMFLOAT3& target , XMFLOAT3& ansvec)
{
	DX11Vec3Normalize(ansvec , target);
}


float LCMath::Lerp(float start , float end , float alpha)
{
	return (1 - alpha)*start + alpha * end;
}

XMFLOAT3 LCMath::Lerp(const XMFLOAT3& start , const XMFLOAT3& end , float alpha)
{
	XMFLOAT3 result;

	result.x = Lerp(start.x , end.x , alpha);
	result.y = Lerp(start.y , end.y , alpha);
	result.z = Lerp(start.z , end.z , alpha);

	return result;
}