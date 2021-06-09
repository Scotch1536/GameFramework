#include "CTransform.h"
#include "DX11Settransform.h"
#include "CChildTransform.h"

CTransform::CTransform()
{
	DX11MtxIdentity(mWorldMatrix);
}

CTransform::CTransform(CActor& partner):CTransform()
{}

void CTransform::AddChildTransform(CChildTransform& child)
{
	mChildTransform.emplace_back(&child);
}

void CTransform::Update()
{
	if(mShouldUpdateMatrix)
	{
		mShouldUpdateMatrix = false;

		XMFLOAT4X4 rotMatrix = mRotation.GenerateMatrix(*this);

		mWorldMatrix._11 = mScale.x * rotMatrix._11;
		mWorldMatrix._12 = mScale.y * rotMatrix._12;
		mWorldMatrix._13 = mScale.z * rotMatrix._13;

		mWorldMatrix._21 = mScale.x * rotMatrix._21;
		mWorldMatrix._22 = mScale.y * rotMatrix._22;
		mWorldMatrix._23 = mScale.z * rotMatrix._23;

		mWorldMatrix._31 = mScale.x * rotMatrix._31;
		mWorldMatrix._32 = mScale.y * rotMatrix._32;
		mWorldMatrix._33 = mScale.z * rotMatrix._33;

		mWorldMatrix._41 = mLocation.x;
		mWorldMatrix._42 = mLocation.y;
		mWorldMatrix._43 = mLocation.z;
	}

	for(auto& child : mChildTransform)
	{
		child->Update();
	}
}

void CTransform::RequestSetMatrix()
{
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD , mWorldMatrix);
}