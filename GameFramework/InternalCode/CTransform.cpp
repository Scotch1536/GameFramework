#include "CTransform.h"
#include "DX11Settransform.h"
#include "CChildTransform.h"
#include "dx11mathutil.h"
#include "LCMath.h"

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
	//bool isSLerp = rotation.Update();
	rotation.Update();

	if(!LCMath::CompareFloat3(location , mCompareLocation) || !LCMath::CompareFloat3(scale , mCompareScale) || !rotation.GetIsNowCompareResult())
	{
		mShouldUpdateMatrix = true;
		mCompareLocation = location;
		mCompareScale = scale;
	}


	if(mShouldUpdateMatrix)
	{
		//if(isSLerp != true)mShouldUpdateMatrix = false;
		mShouldUpdateMatrix = false;

		for(auto& child : mChildTransform)
		{
			child->mShouldUpdateMatrix = true;
		}

		LCMath::UpdateMatrix(location , scale , rotation.GenerateMatrix(*this) , mWorldMatrix);
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