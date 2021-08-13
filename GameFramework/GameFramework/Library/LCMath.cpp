#include <cmath>
#include "LCMath.h"

#include "../ExternalCode/dx11mathutil.h"

const XMFLOAT4& LCMath::TransformFromEulerAnglesToQuaternion(const XMFLOAT3& axisX, const XMFLOAT3& axisY, const XMFLOAT3& axisZ,
	const XMFLOAT3& eulerAngle, XMFLOAT4& resultQua)
{
	XMFLOAT4 qtx, qty, qtz;

	CreateFromAxisAndAngleToQuaternion(axisX, XMConvertToRadians(eulerAngle.x), qtx);
	CreateFromAxisAndAngleToQuaternion(axisY, XMConvertToRadians(eulerAngle.y), qty);
	CreateFromAxisAndAngleToQuaternion(axisZ, XMConvertToRadians(eulerAngle.z), qtz);

	DX11QtMul(resultQua, qtx, qty);
	DX11QtMul(resultQua, resultQua, qtz);

	return resultQua;
}

XMFLOAT4 LCMath::TransformFromEulerAnglesToQuaternion(const XMFLOAT3& axisX, const XMFLOAT3& axisY, const XMFLOAT3& axisZ,
	const XMFLOAT3& eulerAngle)
{
	XMFLOAT4 qtx, qty, qtz;
	XMFLOAT4 result;

	CreateFromAxisAndAngleToQuaternion(axisX, XMConvertToRadians(eulerAngle.x), qtx);
	CreateFromAxisAndAngleToQuaternion(axisY, XMConvertToRadians(eulerAngle.y), qty);
	CreateFromAxisAndAngleToQuaternion(axisZ, XMConvertToRadians(eulerAngle.z), qtz);

	DX11QtMul(result, qtx, qty);
	DX11QtMul(result, result, qtz);

	return result;
}

const XMFLOAT3& LCMath::TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua, XMFLOAT3& resultAngle)
{
	double pitch, yaw, roll;

	//double q0q0 = qua.x * qua.x;
	//double q0q1 = qua.x * qua.y;
	//double q0q2 = qua.x * qua.z;
	//double q0q3 = qua.x * qua.w;
	//double q1q1 = qua.y * qua.y;
	//double q1q2 = qua.y * qua.z;
	//double q1q3 = qua.y * qua.w;
	//double q2q2 = qua.z * qua.z;
	//double q2q3 = qua.z * qua.w;
	//double q3q3 = qua.w * qua.w;

	//pitch = std::atan2(2.0 * (q2q3 + q0q1) , q0q0 - q1q1 - q2q2 + q3q3);
	//yaw = std::asin(2.0 * (q0q2 - q1q3));
	//roll = std::atan2(2.0 * (q1q2 + q0q3) , q0q0 + q1q1 - q2q2 - q3q3);

	double r11, r12, r21, r31, r32;

	r11 = -2 * (qua.y*qua.z - qua.w*qua.x);
	r12 = qua.w*qua.w - qua.x*qua.x - qua.y*qua.y + qua.z*qua.z;
	r21 = 2 * (qua.x*qua.z + qua.w*qua.y);
	r31 = -2 * (qua.x*qua.y + qua.w*qua.z);
	r32 = qua.w*qua.w + qua.x*qua.x - qua.y*qua.y - qua.z*qua.z;

	pitch = std::atan2(r31, r32);
	yaw = std::asin(r21);
	roll = std::atan2(r11, r12);

	resultAngle.x = XMConvertToDegrees(pitch);
	resultAngle.y = XMConvertToDegrees(yaw);
	resultAngle.z = XMConvertToDegrees(roll);

	return resultAngle;
}

XMFLOAT3 LCMath::TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua)
{
	XMFLOAT3 result;

	double pitch, yaw, roll;

	double r11, r12, r21, r31, r32;

	r11 = -2 * (qua.y*qua.z - qua.w*qua.x);
	r12 = qua.w*qua.w - qua.x*qua.x - qua.y*qua.y + qua.z*qua.z;
	r21 = 2 * (qua.x*qua.z + qua.w*qua.y);
	r31 = -2 * (qua.x*qua.y + qua.w*qua.z);
	r32 = qua.w*qua.w + qua.x*qua.x - qua.y*qua.y - qua.z*qua.z;

	pitch = std::atan2(r31, r32);
	yaw = std::asin(r21);
	roll = std::atan2(r11, r12);

	result.x = XMConvertToDegrees(pitch);
	result.y = XMConvertToDegrees(yaw);
	result.z = XMConvertToDegrees(roll);

	return result;
}

void LCMath::IdentityMatrix(XMFLOAT4X4& target)
{
	XMStoreFloat4x4(&target , XMMatrixIdentity());
}

const XMFLOAT4X4& LCMath::UpdateMatrix(const XMFLOAT3& location , const XMFLOAT3& scale , const XMFLOAT4X4& rotMTX , XMFLOAT4X4& resultMTX)
{
	XMFLOAT4X4 trans;
	DX11MtxScale(scale.x, scale.y, scale.z, resultMTX);
	DX11MtxMultiply(resultMTX, resultMTX, rotMTX);
	DX11MtxTranslation(location, trans);
	DX11MtxMultiply(resultMTX, resultMTX, trans);

	//resultMTX._11 = scale.x * rotMTX._11;
	//resultMTX._12 = scale.y * rotMTX._12;
	//resultMTX._13 = scale.z * rotMTX._13;

	//resultMTX._21 = scale.x * rotMTX._21;
	//resultMTX._22 = scale.y * rotMTX._22;
	//resultMTX._23 = scale.z * rotMTX._23;

	//resultMTX._31 = scale.x * rotMTX._31;
	//resultMTX._32 = scale.y * rotMTX._32;
	//resultMTX._33 = scale.z * rotMTX._33;

	//resultMTX._41 = location.x;
	//resultMTX._42 = location.y;
	//resultMTX._43 = location.z;
	//resultMTX._44 = 1;

	return resultMTX;
}

XMFLOAT4X4 LCMath::UpdateMatrix(const XMFLOAT3& location, const XMFLOAT3& scale, const XMFLOAT4X4& rotMTX)
{
	XMFLOAT4X4 result;

	XMFLOAT4X4 trans;
	DX11MtxScale(scale.x, scale.y, scale.z, result);
	DX11MtxMultiply(result, result, rotMTX);
	DX11MtxTranslation(location, trans);
	DX11MtxMultiply(result, result, trans);

	return result;
}

const XMFLOAT4X4& LCMath::InverseMatrix(const XMFLOAT4X4& target, XMFLOAT4X4& resultMTX)
{
	XMMATRIX mat = XMLoadFloat4x4(&target);
	XMMATRIX inverseMTX = XMMatrixInverse(nullptr, mat);
	XMStoreFloat4x4(&resultMTX, inverseMTX);

	return resultMTX;
}

XMFLOAT4X4 LCMath::InverseMatrix(const XMFLOAT4X4& target)
{
	XMFLOAT4X4 result;

	XMMATRIX mat = XMLoadFloat4x4(&target);
	XMMATRIX inverseMTX = XMMatrixInverse(nullptr, mat);
	XMStoreFloat4x4(&result, inverseMTX);

	return result;
}

bool LCMath::CompareFloat3(const XMFLOAT3& target1 , const XMFLOAT3& target2)
{
	if (target1.x != target2.x)return false;
	if (target1.y != target2.y)return false;
	if (target1.z != target2.z)return false;

	return true;
}

bool LCMath::CompareMatrix(const XMFLOAT4X4& target1, const XMFLOAT4X4& target2)
{
	if (target1._11 != target2._11)return false;
	if (target1._12 != target2._12)return false;
	if (target1._13 != target2._13)return false;
	if (target1._14 != target2._14)return false;

	if (target1._21 != target2._21)return false;
	if (target1._22 != target2._22)return false;
	if (target1._23 != target2._23)return false;
	if (target1._24 != target2._24)return false;

	if (target1._31 != target2._31)return false;
	if (target1._32 != target2._32)return false;
	if (target1._33 != target2._33)return false;
	if (target1._34 != target2._34)return false;

	if (target1._41 != target2._41)return false;
	if (target1._42 != target2._42)return false;
	if (target1._43 != target2._43)return false;
	if (target1._44 != target2._44)return false;

	return true;
}

const XMFLOAT4& LCMath::CreateFromAxisAndAngleToQuaternion(const XMFLOAT3& axis, const float& angle, XMFLOAT4& result)
{
	XMVECTOR axisVec = XMLoadFloat3(&axis);

	XMVECTOR resultVec = XMQuaternionRotationAxis(axisVec, angle);

	XMStoreFloat4(&result, resultVec);

	return result;
}

XMFLOAT4 LCMath::CreateFromAxisAndAngleToQuaternion(const XMFLOAT3& axis, const float& angle)
{
	XMFLOAT4 result;

	XMVECTOR axisVec = XMLoadFloat3(&axis);

	XMVECTOR resultVec = XMQuaternionRotationAxis(axisVec, angle);

	XMStoreFloat4(&result, resultVec);

	return result;
}

const XMFLOAT4& LCMath::CalcQuaternionMultiply(const XMFLOAT4& qua1, const XMFLOAT4& qua2, XMFLOAT4& result)
{
	DX11QtMul(result, qua1, qua2);

	return result;
}

XMFLOAT4 LCMath::CalcQuaternionMultiply(const XMFLOAT4& qua1, const XMFLOAT4& qua2)
{
	XMFLOAT4 result;

	DX11QtMul(result, qua1, qua2);

	return result;
}

const XMFLOAT3& LCMath::CalcFloat3FromStartToGoal(const XMFLOAT3& start, const XMFLOAT3& goal, XMFLOAT3& result)
{
	XMVECTOR startVec = XMLoadFloat3(&start);
	XMVECTOR goalVec = XMLoadFloat3(&goal);

	XMStoreFloat3(&result, XMVectorSubtract(goalVec, startVec));

	return result;
}

XMFLOAT3 LCMath::CalcFloat3FromStartToGoal(const XMFLOAT3& start, const XMFLOAT3& goal)
{
	XMFLOAT3 result;

	XMVECTOR startVec = XMLoadFloat3(&start);
	XMVECTOR goalVec = XMLoadFloat3(&goal);

	XMStoreFloat3(&result, XMVectorSubtract(goalVec, startVec));

	return result;
}

const XMFLOAT3& LCMath::CalcFloat3Addition(const XMFLOAT3& target, const XMFLOAT3& vector, XMFLOAT3& resultVec)
{
	resultVec.x = target.x + vector.x;
	resultVec.y = target.y + vector.y;
	resultVec.z = target.z + vector.z;

	return resultVec;
}

XMFLOAT3 LCMath::CalcFloat3Addition(const XMFLOAT3& target, const XMFLOAT3& vector)
{
	XMFLOAT3 resultVec;

	resultVec.x = target.x + vector.x;
	resultVec.y = target.y + vector.y;
	resultVec.z = target.z + vector.z;

	return resultVec;
}

const float& LCMath::CalcFloat3Length(const XMFLOAT3& target, float& result)
{
	DX11Vec3Length(target, result);

	return result;
}

float LCMath::CalcFloat3Length(const XMFLOAT3& target)
{
	float result;

	DX11Vec3Length(target, result);

	return result;
}

const XMFLOAT3& LCMath::CalcFloat3Normalize(const XMFLOAT3& target, XMFLOAT3& result)
{
	DX11Vec3Normalize(result, target);

	return result;
}

XMFLOAT3 LCMath::CalcFloat3Normalize(const XMFLOAT3& target)
{
	XMFLOAT3 result;

	DX11Vec3Normalize(result, target);

	return result;
}

const float& LCMath::CalcFloat3Dot(const XMFLOAT3& target1, const XMFLOAT3& target2, float& result)
{
	DX11Vec3Dot(result, target1, target2);

	return result;
}

float LCMath::CalcFloat3Dot(const XMFLOAT3& target1, const XMFLOAT3& target2)
{
	float result;

	DX11Vec3Dot(result, target1, target2);

	return result;
}

const XMFLOAT3& LCMath::CalcFloat3Cross(const XMFLOAT3& target1, const XMFLOAT3& target2, XMFLOAT3& result)
{
	DX11Vec3Cross(result, target1, target2);

	return result;
}

XMFLOAT3 LCMath::CalcFloat3Cross(const XMFLOAT3& target1, const XMFLOAT3& target2)
{
	XMFLOAT3 result;

	DX11Vec3Cross(result, target1, target2);

	return result;
}

const XMFLOAT3& LCMath::CalcFloat3Scalar(const XMFLOAT3& target, const float& scalar, XMFLOAT3& result)
{
	result.x = target.x * scalar;
	result.y = target.y * scalar;
	result.z = target.z * scalar;

	return result;
}

XMFLOAT3 LCMath::CalcFloat3Scalar(const XMFLOAT3& target, const float& scalar)
{
	XMFLOAT3 result;

	result.x = target.x * scalar;
	result.y = target.y * scalar;
	result.z = target.z * scalar;

	return result;
}

const XMFLOAT3& LCMath::CalcFloat3MultplyMatrix(const XMFLOAT3& target, const XMFLOAT4X4& mtx, XMFLOAT3& result)
{
	DX11Vec3MulMatrix(result, target, mtx);

	return result;
}

XMFLOAT3 LCMath::CalcFloat3MultplyMatrix(const XMFLOAT3& target, const XMFLOAT4X4& mtx)
{
	XMFLOAT3 result;
	DX11Vec3MulMatrix(result, target, mtx);

	return result;
}

const void LCMath::CalcFloat3MinMax(const std::vector<XMFLOAT3>& vertices, XMFLOAT3& resultMin, XMFLOAT3& resultMax)
{
	resultMin = {0,0,0};
	resultMax = {0,0,0};

	for (auto& v : vertices)
	{
		if (resultMin.x > v.x)	resultMin.x = v.x;
		else if (resultMax.x < v.x) resultMax.x = v.x;

		if (resultMin.y > v.y)	resultMin.y = v.y;
		else if (resultMax.y < v.y) resultMax.y = v.y;

		if (resultMin.z > v.z)	resultMin.z = v.z;
		else if (resultMax.z < v.z) resultMax.z = v.z;
	}
}

const float& LCMath::Lerp(const float& start, const float& end, const float& alpha, float& result)
{
	result = (1 - alpha)*start + alpha * end;

	return result;
}

float LCMath::Lerp(const float& start, const float& end, const float& alpha)
{
	float result;

	result = (1 - alpha)*start + alpha * end;

	return result;
}

const XMFLOAT3& LCMath::Lerp(const XMFLOAT3& start, const XMFLOAT3& end, const float& alpha, XMFLOAT3& result)
{
	Lerp(start.x, end.x, alpha, result.x);
	Lerp(start.y, end.y, alpha, result.y);
	Lerp(start.z, end.z, alpha, result.z);

	return result;
}

XMFLOAT3 LCMath::Lerp(const XMFLOAT3& start, const XMFLOAT3& end, const float& alpha)
{
	XMFLOAT3 result;

	Lerp(start.x, end.x, alpha, result.x);
	Lerp(start.y, end.y, alpha, result.y);
	Lerp(start.z, end.z, alpha, result.z);

	return result;
}

const XMFLOAT4& LCMath::Lerp(const XMFLOAT4& start, const XMFLOAT4& end, const float& alpha, XMFLOAT4& result)
{
	Lerp(start.x, end.x, alpha, result.x);
	Lerp(start.y, end.y, alpha, result.y);
	Lerp(start.z, end.z, alpha, result.z);
	Lerp(start.w, end.w, alpha, result.w);

	return result;
}

XMFLOAT4 LCMath::Lerp(const XMFLOAT4& start, const XMFLOAT4& end, const float& alpha)
{
	XMFLOAT4 result;

	Lerp(start.x, end.x, alpha, result.x);
	Lerp(start.y, end.y, alpha, result.y);
	Lerp(start.z, end.z, alpha, result.z);
	Lerp(start.w, end.w, alpha, result.w);

	return result;
}