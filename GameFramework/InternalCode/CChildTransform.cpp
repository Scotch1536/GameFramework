#include "CChildTransform.h"
#include "LCMath.h"
#include "dx11mathutil.h"

CChildTransform::CChildTransform(CTransform& parent):mParentTransform(parent)
{
	static_cast<ITransform&>(parent).AddChildTransform(*this);
}

void CChildTransform::Update()
{
	if(mShouldUpdateMatrix)
	{
		mShouldUpdateMatrix = false;

		XMFLOAT3 parentLocation = mParentTransform.location;
		XMFLOAT3 parentScale = mParentTransform.scale;
		XMFLOAT3 parentAngle = mParentTransform.rotation.angle;

		XMFLOAT3 ansLocation;
		XMFLOAT3 ansScale;
		XMFLOAT3 ansAngle;

		XMFLOAT3 bufAngle = rotation.angle;

		ansLocation.x = location.x + parentLocation.x;
		ansLocation.y = location.y + parentLocation.y;
		ansLocation.z = location.z + parentLocation.z;

		ansScale.x = scale.x + parentScale.x;
		ansScale.y = scale.y + parentScale.y;
		ansScale.z = scale.z + parentScale.z;

		ansAngle.x = bufAngle.x + parentAngle.x;
		ansAngle.y = bufAngle.y + parentAngle.y;
		ansAngle.z = bufAngle.z + parentAngle.z;

		/*mRotation.Update();

		XMFLOAT4 parentQua = mParentTransform.GetRotation().GetQuaternion();
		XMFLOAT4 ansQua;

		DX11QtMul(ansQua , parentQua , mRotation.GetQuaternion());*/

		XMFLOAT4 ansQua;

		LCMath::TransformFromEulerAnglesToQuaternion(ansAngle , ansQua);

		rotation.SetQuaternion(*this , ansQua);

		XMFLOAT4X4 ansMTX;

		//クォータニオンから行列を作成
		DX11MtxFromQt(ansMTX , ansQua);

		LCMath::UpdateMatrix(ansLocation , ansScale , ansMTX , mWorldMatrix);
	}
}