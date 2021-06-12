#include "../Math/LCMath.h"
#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/dx11mathutil.h"

#include "CChildTransform.h"

CChildTransform::CChildTransform(CTransform& parent):mParentTransform(parent)
{
	static_cast<ITransform&>(mParentTransform).AttachChildTransform(*this);
}

CChildTransform::~CChildTransform()
{
	mParentTransform.DetachChildTransform(*this);
}

void CChildTransform::Update()
{
	CTransform::Update();

	DX11MtxMultiply(mParentCompositionMatrix , mWorldMatrix , mParentTransform.GetWorldMatrix(*this));
}

void CChildTransform::RequestSetMatrix()
{
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD , mParentCompositionMatrix);
}

//void CChildTransform::Update()
//{
//	if(mShouldUpdateMatrix)
//	{
//		mShouldUpdateMatrix = false;
//
//		XMFLOAT3 parentLocation = mParentTransform.Location;
//		XMFLOAT3 parentScale = mParentTransform.Scale;
//		XMFLOAT3 parentAngle = mParentTransform.Rotation.Angle;
//
//		XMFLOAT3 ansLocation;
//		XMFLOAT3 ansScale;
//		XMFLOAT3 ansAngle;
//
//		XMFLOAT3 bufAngle = Rotation.Angle;
//
//		ansLocation.x = Location.x + parentLocation.x;
//		ansLocation.y = Location.y + parentLocation.y;
//		ansLocation.z = Location.z + parentLocation.z;
//
//		ansScale.x = Scale.x + parentScale.x;
//		ansScale.y = Scale.y + parentScale.y;
//		ansScale.z = Scale.z + parentScale.z;
//
//		ansAngle.x = bufAngle.x + parentAngle.x;
//		ansAngle.y = bufAngle.y + parentAngle.y;
//		ansAngle.z = bufAngle.z + parentAngle.z;
//
//		XMFLOAT4 ansQua;
//
//		LCMath::TransformFromEulerAnglesToQuaternion(ansAngle , ansQua);
//
//		Rotation.SetQuaternion(*this , ansQua);
//
//		XMFLOAT4X4 ansMTX;
//
//		//クォータニオンから行列を作成
//		DX11MtxFromQt(ansMTX , ansQua);
//
//		LCMath::UpdateMatrix(ansLocation , ansScale , ansMTX , mWorldMatrix);
//	}
//}