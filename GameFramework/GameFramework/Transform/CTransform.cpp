#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/dx11mathutil.h"
#include "../Math/LCMath.h"

#include "CTransform.h"
#include "CChildTransform.h"

CTransform::CTransform()
{
	DX11MtxIdentity(mWorldMatrix);
}

CTransform::CTransform(CActor& partner):CTransform()
{}

void CTransform::AttachChildTransform(CChildTransform& targetChild)
{
	mChildTransform.emplace_back(&targetChild);
}

void CTransform::DetachChildTransform(CChildTransform& targetChild)
{
	for(auto itr = mChildTransform.begin(); itr != mChildTransform.end(); ++itr)
	{
		if((*itr) == &targetChild)
		{
			mChildTransform.erase(itr);
			mChildTransform.shrink_to_fit();
			break;
		}
	}
}

void CTransform::Update()
{
	Rotation.Update();

	if(!LCMath::CompareFloat3(Location , mCompareLocation) || !LCMath::CompareFloat3(Scale , mCompareScale) || !Rotation.GetIsNowCompareResult())
	{
		mShouldUpdateMatrix = true;
		mCompareLocation = Location;
		mCompareScale = Scale;
	}

	if(mShouldUpdateMatrix)
	{
		mShouldUpdateMatrix = false;

		for(auto& child : mChildTransform)
		{
			child->mShouldUpdateMatrix = true;
		}

		LCMath::UpdateMatrix(Location , Scale , Rotation.GenerateMatrix(*this) , mWorldMatrix);
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