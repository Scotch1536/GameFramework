#include "CChildTransform.h"

CChildTransform::CChildTransform(CTransform& parent):mParentTransform(parent)
{
	static_cast<ITransform&>(parent).AddChildTransform(*this);
}

void CChildTransform::Update()
{
	XMFLOAT3 parentLocation=mParentTransform.GetLocation();
	XMFLOAT3 parentScale=mParentTransform.GetScale();
	XMFLOAT3 parentAngle=mParentTransform.GetRotation();
	XMFLOAT3 ansAngle = mRotation.GetAngle();

	mLocation.x += parentLocation.x;
	mLocation.y += parentLocation.y;
	mLocation.z += parentLocation.z;

	mScale.x += parentScale.x;
	mScale.y += parentScale.y;
	mScale.z += parentScale.z;

	ansAngle.x += parentAngle.x;
	ansAngle.y += parentAngle.y;
	ansAngle.z += parentAngle.z;

	mRotation.SetAngle(ansAngle);

	CTransform::Update();
}