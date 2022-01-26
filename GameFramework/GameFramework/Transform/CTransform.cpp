#include "../ExternalCode/DX11Settransform.h"
#include "../Managers/CGameManager.h"
#include "../Library/LCMath.h"
#include "../Actor/CActor.h"
#include "../Components/CLineComponent.h"

#include "CTransform.h"

CTransform::CTransform(IActor& partner):Rotation(*this) , mOwnerInterface(partner)
{
	LCMath::IdentityMatrix(mWorldMatrixSelf);
	LCMath::IdentityMatrix(mWorldMatrixResult);
}

CTransform::CTransform(IActor& partner , CTransform& parentTrans): CTransform(partner)
{
	parentTrans.AttachTransform(*this);
}

CTransform::~CTransform()
{
	if(mParentTransform != nullptr)mParentTransform->DetachTransform(*this);
	for(auto& child : mChildTransform)
	{
		child->DetachTransform(*this);
	}
}

void CTransform::RequestDebugLine()
{
#ifdef _DEBUG
	if(!mDoDrawDebugLine)
	{
		mDoDrawDebugLine = true;
		new CLineComponent(mOwnerInterface.GetActor() , { 0.0f,0.0f,0.0f } , { 1.0f , 0.0f , 0.0f } , 50.0f , { 1.0f,0.0f,0.0f,1.0f } , this);
		new CLineComponent(mOwnerInterface.GetActor() , { 0.0f,0.0f,0.0f } , { 0.0f , 1.0f , 0.0f } , 50.0f , { 0.0f,1.0f,0.0f,1.0f } , this);
		new CLineComponent(mOwnerInterface.GetActor() , { 0.0f,0.0f,0.0f } , { 0.0f , 0.0f , 1.0f } , 50.0f , { 0.0f,0.0f,1.0f,1.0f } , this);
	}
#endif
}

void CTransform::AttachTransform(CTransform& attachTarget)
{
	//������q�ɂȂ�g�����X�t�H�[���̃��[���h�ϊ��s���e�Ƃ̑��΍s��ɕϊ�
	XMFLOAT4X4 attachTargetMTX = attachTarget.GetWorldMatrixResult();
	XMFLOAT4X4 parentInvMTX = LCMath::InverseMatrix(mWorldMatrixResult);
	LCMath::CalcMatrixMultply(attachTargetMTX , parentInvMTX , attachTargetMTX);

	//������q�ɂȂ�g�����X�t�H�[���ɑ��΍s����Z�b�g
	attachTarget.SetWorldMatrixSelf(attachTargetMTX);

	attachTarget.mParentTransform = this;
	attachTarget.mIsChild = true;

	mChildTransform.emplace_back(&attachTarget);
}

void CTransform::DetachTransform(CTransform& detachTarget)
{
	if(mParentTransform == &detachTarget)
	{
		mWorldMatrixSelf = mWorldMatrixResult;

		mParentTransform = nullptr;
		mIsChild = false;
	}
	if(mChildTransform.size() != 0)
	{
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
}

void CTransform::SetWorldMatrixSelf(const XMFLOAT4X4& matrix)
{
	mWorldMatrixSelf = matrix;

	Location.x = mWorldMatrixSelf._41;
	Location.y = mWorldMatrixSelf._42;
	Location.z = mWorldMatrixSelf._43;

	Scale.x = LCMath::CalcFloat3Length({ mWorldMatrixSelf._11,mWorldMatrixSelf._12,mWorldMatrixSelf._13 });
	Scale.y = LCMath::CalcFloat3Length({ mWorldMatrixSelf._21,mWorldMatrixSelf._22,mWorldMatrixSelf._23 });
	Scale.z = LCMath::CalcFloat3Length({ mWorldMatrixSelf._31,mWorldMatrixSelf._32,mWorldMatrixSelf._33 });

	mIgnoreUpdateMatrixOnce = true;
}

void CTransform::Update()
{
	Rotation.Update();

	if(!LCMath::CompareFloat3(Location , mLastFrameLocation) || !LCMath::CompareFloat3(Scale , mLastFrameScale) || !Rotation.GetIsSameQuaternionToBeforeFrame())
	{
		if(!mIgnoreUpdateMatrixOnce)
		{
			mShouldUpdateMatrix = true;
		}
		else
		{
			mIgnoreUpdateMatrixOnce = false;
		}

		mLastFrameLocation = Location;
		mLastFrameScale = Scale;
	}

	if(mShouldUpdateMatrix)
	{
		mShouldUpdateMatrix = false;

		LCMath::UpdateMatrix(Location , Scale , Rotation.GenerateMatrix() , mWorldMatrixSelf);

		if(mMatrixUpdateTimeFunction.size() > 0)
		{
			for(auto& func : mMatrixUpdateTimeFunction)
			{
				func();
			}
		}
	}

	if(mParentTransform != nullptr)
	{
		LCMath::CalcMatrixMultply(mWorldMatrixSelf , mParentTransform->GetWorldMatrixResult() , mWorldMatrixResult);

		if(mAttachOption == EAttachOption::LOCATION_ONLY)
		{
			mWorldMatrixResult._11 = mWorldMatrixSelf._11;
			mWorldMatrixResult._12 = mWorldMatrixSelf._12;
			mWorldMatrixResult._13 = mWorldMatrixSelf._13;
			mWorldMatrixResult._21 = mWorldMatrixSelf._21;
			mWorldMatrixResult._22 = mWorldMatrixSelf._22;
			mWorldMatrixResult._23 = mWorldMatrixSelf._23;
			mWorldMatrixResult._31 = mWorldMatrixSelf._31;
			mWorldMatrixResult._32 = mWorldMatrixSelf._32;
			mWorldMatrixResult._33 = mWorldMatrixSelf._33;
		}
	}
	else
	{
		mWorldMatrixResult = mWorldMatrixSelf;
	}

	//�r���{�[�h�Ȃ猋�ʂ̍s��ɏ㏑������
	if(mIsBillboard)
	{
		const XMFLOAT4X4* camera = CGameManager::GetInstance().GetCameraViewMatrix();
		if(camera != nullptr)
		{
			XMFLOAT4X4 inverseCamera;
			XMFLOAT4X4 resultMTX;
			LCMath::InverseMatrix(*camera , inverseCamera);

			LCMath::CalcMatrixMultply(mWorldMatrixSelf , inverseCamera , resultMTX);

			mWorldMatrixResult._11 = resultMTX._11;
			mWorldMatrixResult._12 = resultMTX._12;
			mWorldMatrixResult._13 = resultMTX._13;

			mWorldMatrixResult._21 = resultMTX._21;
			mWorldMatrixResult._22 = resultMTX._22;
			mWorldMatrixResult._23 = resultMTX._23;

			mWorldMatrixResult._31 = resultMTX._31;
			mWorldMatrixResult._32 = resultMTX._32;
			mWorldMatrixResult._33 = resultMTX._33;
		}
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

XMFLOAT3 CTransform::GetRightVectorWorld()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrixResult._11;
	result.y = mWorldMatrixResult._12;
	result.z = mWorldMatrixResult._13;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetUpwardVectorWorld()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrixResult._21;
	result.y = mWorldMatrixResult._22;
	result.z = mWorldMatrixResult._23;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetForwardVectorWorld()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrixResult._31;
	result.y = mWorldMatrixResult._32;
	result.z = mWorldMatrixResult._33;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetRightVectorRelative()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrixSelf._11;
	result.y = mWorldMatrixSelf._12;
	result.z = mWorldMatrixSelf._13;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetUpwardVectorRelative()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrixSelf._21;
	result.y = mWorldMatrixSelf._22;
	result.z = mWorldMatrixSelf._23;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetForwardVectorRelative()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrixSelf._31;
	result.y = mWorldMatrixSelf._32;
	result.z = mWorldMatrixSelf._33;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetWorldLocation()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrixResult._41;
	result.y = mWorldMatrixResult._42;
	result.z = mWorldMatrixResult._43;

	return result;
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

//XMFLOAT3 CTransform::GetWorldRotatorAngle()const
//{
//	XMFLOAT3 angle = Rotation.GetAngle();
//	XMFLOAT3 result;
//
//	if(mParentTransform != nullptr)
//	{
//		result = mParentTransform->GetWorldRotatorAngle();
//
//		result.x += angle.x;
//		result.y += angle.y;
//		result.z += angle.z;
//
//		return result;
//	}
//	else return angle;
//}