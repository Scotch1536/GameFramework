#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/dx11mathutil.h"
#include "../Managers/CGameManager.h"
#include "../Library/LCMath.h"
#include "../Actor/CActor.h"

#include "CTransform.h"

CTransform::CTransform():Rotation(*this)
{
	DX11MtxIdentity(mWorldMatrixSelf);
	DX11MtxIdentity(mWorldMatrixResult);
}

CTransform::CTransform(const CActor& partner):CTransform() {}

CTransform::CTransform(CTransform& partner) : CTransform()
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
	if(mIsBillboard)
	{
		mShouldUpdateMatrix = true;

		XMFLOAT3 angle = Rotation.GetAngle();
		if(angle.x != 0.0f || angle.y != 0)Rotation.SetAngle({ 0.0f,0.0f,angle.z });
	}

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

		if(mIsBillboard)
		{
			XMFLOAT4X4 rotMTX = Rotation.GenerateMatrix();

			const XMFLOAT4X4* camera = CGameManager::GetInstance().GetCameraViewMatrix();
			if(camera != nullptr)
			{
				XMFLOAT4X4 inverseCamera;
				LCMath::InverseMatrix(*camera , inverseCamera);

				inverseCamera._41 = 0.0f;
				inverseCamera._42 = 0.0f;
				inverseCamera._43 = 0.0f;

				//SetMatrixToBillboard(inverseCamera);
				DX11MtxMultiply(rotMTX , inverseCamera , rotMTX);
			}
			LCMath::UpdateMatrix(Location , Scale , rotMTX , mWorldMatrixSelf);
		}
		else
		{
			LCMath::UpdateMatrix(Location , Scale , Rotation.GenerateMatrix() , mWorldMatrixSelf);
		}
	}

	if(mParentTransform != nullptr)
	{
		DX11MtxMultiply(mWorldMatrixResult , mWorldMatrixSelf , mParentTransform->GetWorldMatrixResult());

		//if(mIsBillboard)
		//{
		//	CTransform* bufTrans = mParentTransform;
		//	std::vector<XMFLOAT4X4> inverseMTX;
		//	while(bufTrans != nullptr)
		//	{
		//		XMFLOAT4X4 TransMTX , TransInvMTX;

		//		DX11MtxTranslation(bufTrans->Location , TransMTX);
		//		LCMath::InverseMatrix(TransMTX , TransInvMTX);

		//		auto itr = inverseMTX.begin();
		//		inverseMTX.emplace(itr,TransInvMTX);

		//		AddMatricesToLastMultiply(TransMTX);

		//		bufTrans = bufTrans->mParentTransform;
		//	}

		//	for(auto& invMTX : inverseMTX)
		//	{
		//		DX11MtxMultiply(mWorldMatrixResult , mWorldMatrixResult , invMTX);
		//	}
		//}
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
	//if(mMatrixToBillboard != nullptr)
	//{
	//	DX11MtxMultiply(mWorldMatrixResult , *mMatrixToBillboard , mWorldMatrixResult);
	//}

	//if(mMatricesToLastMultiply.size() != 0)
	//{
	//	for(auto& matrix : mMatricesToLastMultiply)
	//	{
	//		DX11MtxMultiply(mWorldMatrixResult , mWorldMatrixResult , matrix);
	//	}
	//	mMatricesToLastMultiply.clear();
	//	mMatricesToLastMultiply.shrink_to_fit();
	//}

	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD , mWorldMatrixResult);
}

XMFLOAT3 CTransform::GetRightVector()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrixResult._11;
	result.y = mWorldMatrixResult._12;
	result.z = mWorldMatrixResult._13;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetUpwardVector()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrixResult._21;
	result.y = mWorldMatrixResult._22;
	result.z = mWorldMatrixResult._23;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetForwardVector()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrixResult._31;
	result.y = mWorldMatrixResult._32;
	result.z = mWorldMatrixResult._33;

	LCMath::CalcFloat3Normalize(result , result);

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
	XMFLOAT3 angle = Rotation.GetAngle();
	XMFLOAT3 result;

	if(mParentTransform != nullptr)
	{
		result = mParentTransform->GetWorldRotatorAngle();

		result.x += angle.x;
		result.y += angle.y;
		result.z += angle.z;

		return result;
	}
	else return angle;
}