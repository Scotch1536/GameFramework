//!
//!	@file
//!	@brief �g�����X�t�H�[���V�X�e���̃\�[�X�t�@�C��
//!

#include "../ExternalCode/DX11Settransform.h"
#include "../Managers/CGameManager.h"
#include "../Library/LCMath.h"
#include "../Actor/CActor.h"
#include "../Components/CLineComponent.h"

#include "CTransform.h"

CTransform::CTransform(IActor& partner):Rotation(*this) , mOwnerInterface(partner)
{
	LCMath::IdentityMatrix(mLocalMatrix);
	LCMath::IdentityMatrix(mWorldMatrix);
}

CTransform::CTransform(IActor& partner , CTransform& parentTrans): CTransform(partner)
{
	parentTrans.AttachTransform(*this);
}

CTransform::~CTransform()
{
	//�e������Ȃ玩����؂藣��
	if(mParentTransform != nullptr)mParentTransform->DetachTransform(*this);

	//���݂���Ȃ�
	if(mChildTransform.size() != 0)
	{
		for(auto& child : mChildTransform)
		{
			//�q�Ɏ������f�^�b�`������
			child->DetachTransform(*this);
		}
	}
}

void CTransform::RequestDebugLine()
{
#ifdef _DEBUG
	if(!mDoDrawDebugLine)
	{
		mDoDrawDebugLine = true;

		//���C���R���|�[�l���g�쐬
		new CLineComponent(mOwnerInterface.GetActor() , { 0.0f,0.0f,0.0f } , { 1.0f , 0.0f , 0.0f } , 50.0f , { 1.0f,0.0f,0.0f,1.0f } , this);
		new CLineComponent(mOwnerInterface.GetActor() , { 0.0f,0.0f,0.0f } , { 0.0f , 1.0f , 0.0f } , 50.0f , { 0.0f,1.0f,0.0f,1.0f } , this);
		new CLineComponent(mOwnerInterface.GetActor() , { 0.0f,0.0f,0.0f } , { 0.0f , 0.0f , 1.0f } , 50.0f , { 0.0f,0.0f,1.0f,1.0f } , this);
	}
#endif
}

void CTransform::AttachTransform(CTransform& attachTarget)
{
	//������q�ɂȂ�g�����X�t�H�[���̃��[���h�ϊ��s���e�Ƃ̑��΍s��ɕϊ�
	XMFLOAT4X4 attachTargetMTX = attachTarget.GetWorldMatrix();
	XMFLOAT4X4 parentInvMTX = LCMath::InverseMatrix(mWorldMatrix);
	LCMath::CalcMatrixMultply(attachTargetMTX , parentInvMTX , attachTargetMTX);

	//������q�ɂȂ�g�����X�t�H�[���ɑ��΍s����Z�b�g
	attachTarget.SetLocalMatrix(attachTargetMTX);

	attachTarget.mParentTransform = this;
	attachTarget.mIsChild = true;

	mChildTransform.emplace_back(&attachTarget);
}

void CTransform::DetachTransform(CTransform& detachTarget)
{
	//�e�ƈ�v����Ȃ�
	if(mParentTransform == &detachTarget)
	{
		mLocalMatrix = mWorldMatrix;

		mParentTransform = nullptr;
		mIsChild = false;
	}

	//���݂���Ȃ�
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

void CTransform::SetLocalMatrix(const XMFLOAT4X4& matrix)
{
	mLocalMatrix = matrix;

	Location.x = mLocalMatrix._41;
	Location.y = mLocalMatrix._42;
	Location.z = mLocalMatrix._43;

	Scale.x = LCMath::CalcFloat3Length({ mLocalMatrix._11,mLocalMatrix._12,mLocalMatrix._13 });
	Scale.y = LCMath::CalcFloat3Length({ mLocalMatrix._21,mLocalMatrix._22,mLocalMatrix._23 });
	Scale.z = LCMath::CalcFloat3Length({ mLocalMatrix._31,mLocalMatrix._32,mLocalMatrix._33 });

	mIgnoreUpdateMatrixOnce = true;
}

void CTransform::Update()
{
	//���[�e�[�^�[�X�V
	Rotation.Update();

	//���P�[�V�����A�X�P�[���A���[�e�[�^�[�ǂꂩ��ł��O�t���[���̏��ƈႦ��
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

		//�s��X�V
		LCMath::CreateMatrix(Location , Scale , Rotation.GenerateMatrix() , mLocalMatrix);

		//���݂���Ȃ�
		if(mEventWhenMatrixUpdate.size() > 0)
		{
			//�s��X�V�����s�C�x���g���s��
			for(auto& event : mEventWhenMatrixUpdate)
			{
				event();
			}
		}
	}

	//�e������Ȃ�
	if(mParentTransform != nullptr)
	{
		//���g�̃��[�J���s��ɐe�̃��[���h�s��������Ď��g�̃��[���h�s��Ƃ���i�e�q�t���������s���j
		LCMath::CalcMatrixMultply(mLocalMatrix , mParentTransform->GetWorldMatrix() , mWorldMatrix);

		//���P�[�V�����݂̂̃I�v�V�����Ȃ�
		if(mAttachOption == EAttachOption::LOCATION_ONLY)
		{
			//���s�ړ������ȊO�����ɖ߂�
			mWorldMatrix._11 = mLocalMatrix._11;
			mWorldMatrix._12 = mLocalMatrix._12;
			mWorldMatrix._13 = mLocalMatrix._13;
			mWorldMatrix._21 = mLocalMatrix._21;
			mWorldMatrix._22 = mLocalMatrix._22;
			mWorldMatrix._23 = mLocalMatrix._23;
			mWorldMatrix._31 = mLocalMatrix._31;
			mWorldMatrix._32 = mLocalMatrix._32;
			mWorldMatrix._33 = mLocalMatrix._33;
		}
	}
	else
	{
		mWorldMatrix = mLocalMatrix;
	}

	//�r���{�[�h�Ȃ猋�ʂ̍s��ɏ㏑������
	if(mIsBillboard)
	{
		//���ݕ`��S���̃J�����̃r���[�s����擾
		const XMFLOAT4X4* camera = CGameManager::GetInstance().GetCameraViewMatrix();

		//�擾�ł��Ă����
		if(camera != nullptr)
		{
			XMFLOAT4X4 inverseCamera;
			XMFLOAT4X4 resultMTX;

			//�r���[�s��̋t�s��Z�o
			LCMath::InverseMatrix(*camera , inverseCamera);

			//���[�J���s��ɋt�s�����Z
			LCMath::CalcMatrixMultply(mLocalMatrix , inverseCamera , resultMTX);

			//��]�����̂ݏ㏑��
			mWorldMatrix._11 = resultMTX._11;
			mWorldMatrix._12 = resultMTX._12;
			mWorldMatrix._13 = resultMTX._13;

			mWorldMatrix._21 = resultMTX._21;
			mWorldMatrix._22 = resultMTX._22;
			mWorldMatrix._23 = resultMTX._23;

			mWorldMatrix._31 = resultMTX._31;
			mWorldMatrix._32 = resultMTX._32;
			mWorldMatrix._33 = resultMTX._33;
		}
	}

	//���݂���Ȃ�q���X�V
	if(mChildTransform.size() != 0)
	{
		for(auto& child : mChildTransform)
		{
			child->Update();
		}
	}
}

void CTransform::RequestSetMatrix()
{
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD , mWorldMatrix);
}

XMFLOAT3 CTransform::GetWorldRightVector()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrix._11;
	result.y = mWorldMatrix._12;
	result.z = mWorldMatrix._13;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetWorldUpwardVector()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrix._21;
	result.y = mWorldMatrix._22;
	result.z = mWorldMatrix._23;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetWorldForwardVector()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrix._31;
	result.y = mWorldMatrix._32;
	result.z = mWorldMatrix._33;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetLocalRightVector()const
{
	XMFLOAT3 result;

	result.x = mLocalMatrix._11;
	result.y = mLocalMatrix._12;
	result.z = mLocalMatrix._13;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetLocalUpwardVector()const
{
	XMFLOAT3 result;

	result.x = mLocalMatrix._21;
	result.y = mLocalMatrix._22;
	result.z = mLocalMatrix._23;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetLocalForwardVector()const
{
	XMFLOAT3 result;

	result.x = mLocalMatrix._31;
	result.y = mLocalMatrix._32;
	result.z = mLocalMatrix._33;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetWorldLocation()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrix._41;
	result.y = mWorldMatrix._42;
	result.z = mWorldMatrix._43;

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