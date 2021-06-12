#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/dx11mathutil.h"
#include "../Math/LCMath.h"
#include "../Actor/CActor.h"

#include "CTransform.h"

CTransform::CTransform()
{
	DX11MtxIdentity(mWorldMatrixSelf);
	DX11MtxIdentity(mWorldMatrixResult);
}

CTransform::CTransform(IActor& partner):CTransform()
{
	partner.GetTransform().AttachTransform(*this);
}

CTransform::~CTransform()
{
	if(mParentTransform != nullptr)mParentTransform->DetachTransform(*this);
	for(auto child : mChildTransform)
	{
		child->DetachTransform(*this);
	}
}

void CTransform::AttachTransform(CTransform& attachTarget)
{
	mChildTransform.emplace_back(&attachTarget);
	attachTarget.mParentTransform = this;
	attachTarget.mIsChild = true;
}

void CTransform::DetachTransform(CTransform& detachTarget)
{
	if(mParentTransform == &detachTarget)
	{
		mParentTransform = nullptr;
		mIsChild = false;
	}
	for(auto itr = mChildTransform.begin(); itr != mChildTransform.end(); ++itr)
	{
		if((*itr) == &detachTarget)
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

	if(!LCMath::CompareFloat3(Location , mCompareLocation) || !LCMath::CompareFloat3(Scale , mCompareScale) || !Rotation.GetIsSameAngle())
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

		LCMath::UpdateMatrix(Location , Scale , Rotation.GenerateMatrix(*this) , mWorldMatrixSelf);
	}

	if(mParentTransform != nullptr)
	{
		DX11MtxMultiply(mWorldMatrixResult , mWorldMatrixSelf , mParentTransform->GetWorldMatrixSelf(*this));
	}
	else
	{
		mWorldMatrixResult = mWorldMatrixSelf;
	}

	for(auto& child : mChildTransform)
	{
		child->Update();
	}
}

void CTransform::RequestSetMatrix()
{
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD , mWorldMatrixResult);
}