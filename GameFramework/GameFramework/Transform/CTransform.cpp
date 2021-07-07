#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/dx11mathutil.h"
#include "../Library/LCMath.h"
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

CTransform::CTransform(CTransform& partner):CTransform()
{
	partner.AttachTransform(*this);
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

	if(!LCMath::CompareFloat3(Location , mLastFrameLocation) || !LCMath::CompareFloat3(Scale , mLastFrameScale) || !Rotation.GetIsSameAngle())
	{
		mShouldUpdateMatrix = true;
		mLastFrameLocation = Location;
		mLastFrameScale = Scale;
	}
	if(mShouldUpdateMatrix)
	{
		mShouldUpdateMatrix = false;

		LCMath::UpdateMatrix(Location , Scale , Rotation.GenerateMatrix() , mWorldMatrixSelf);
	}

	if(mParentTransform != nullptr)
	{
		DX11MtxMultiply(mWorldMatrixResult , mWorldMatrixSelf , mParentTransform->GetWorldMatrixResult());
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

XMFLOAT3 CTransform::GetRightVector()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrixResult._11;
	result.y = mWorldMatrixResult._12;
	result.z = mWorldMatrixResult._13;

	DX11Vec3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetUpwardVector()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrixResult._21;
	result.y = mWorldMatrixResult._22;
	result.z = mWorldMatrixResult._23;

	DX11Vec3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetForwardVector()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrixResult._31;
	result.y = mWorldMatrixResult._32;
	result.z = mWorldMatrixResult._33;

	DX11Vec3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetWorldLocation()const
{
	XMFLOAT3 result;

	if(mParentTransform != nullptr)
	{
		result = mParentTransform->GetWorldLocation();

		result.x += Location.x;
		result.y += Location.y;
		result.z += Location.z;

		return result;
	}
	else return Location;
}

XMFLOAT3 CTransform::GetWorldScale()const
{
	XMFLOAT3 result;

	if(mParentTransform != nullptr)
	{
		result = mParentTransform->GetWorldScale();

		result.x *= Scale.x;
		result.y *= Scale.y;
		result.z *= Scale.z;

		return result;
	}
	else return Scale;
}

XMFLOAT3 CTransform::GetWorldRotatorAngle()const
{
	XMFLOAT3 result;

	if(mParentTransform != nullptr)
	{
		result = mParentTransform->GetWorldRotatorAngle();

		result.x += Rotation.Angle.x;
		result.y += Rotation.Angle.y;
		result.z += Rotation.Angle.z;

		return result;
	}
	else return Rotation.Angle;
}