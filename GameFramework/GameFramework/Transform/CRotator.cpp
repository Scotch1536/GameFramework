#include "../Library/LCMath.h"

#include "CRotator.h"
#include "CTransform.h"

CRotator::CRotator(CTransform& partner):mPartner(partner)
{
	LCMath::IdentityQuaternion(mQuaternion);
	LCMath::IdentityQuaternion(mLastFrameQuaternion);
}

//void CRotator::UpdateAngle(float& angle)
//{
//	if(angle < 0.0f)
//	{
//		angle = 360.0f + angle;
//	}
//	else if(angle > 360.0f)
//	{
//		angle = angle - 360.0f;
//	}
//}

bool CRotator::Update()
{
	if(!LCMath::CompareFloat4(mQuaternion , mLastFrameQuaternion))
	{
		mLastFrameQuaternion = mQuaternion;

		mIsSameQuaternionToBeforeFrame = false;
	}
	else
	{
		mIsSameQuaternionToBeforeFrame = true;
	}
	return false;
}

XMFLOAT4X4 CRotator::GenerateMatrix()
{
	XMFLOAT4X4 ansMTX;

	//�N�H�[�^�j�I������s����쐬
	LCMath::CalcMatrixFromQuaternion(mQuaternion , ansMTX);

	return ansMTX;
}

void CRotator::SetAngle(const XMFLOAT3& angle)
{
	LCMath::TransformFromEulerAnglesToQuaternion({ 1.0f,0.0f,0.0f } , { 0.0f , 1.0f , 0.0f } ,
		{ 0.0f,0.0f,1.0f } , angle , mQuaternion);

	mPartner.Update();
}

void CRotator::AddAngleRelative(const XMFLOAT3& angle)
{
	XMFLOAT4 qua;

	LCMath::TransformFromEulerAnglesToQuaternion(mPartner.GetRightVectorRelative() , mPartner.GetUpwardVectorRelative() ,
		mPartner.GetForwardVectorRelative() , angle , qua);
	LCMath::CalcQuaternionMultiply(mQuaternion , qua , mQuaternion);

	mPartner.Update();
}

void CRotator::AddAngleWorld(const XMFLOAT3& angle)
{
	XMFLOAT4 qua;

	LCMath::TransformFromEulerAnglesToQuaternion(mPartner.GetRightVectorWorld() , mPartner.GetUpwardVectorWorld() ,
		mPartner.GetForwardVectorWorld() , angle , qua);
	LCMath::CalcQuaternionMultiply(mQuaternion , qua , mQuaternion);

	mPartner.Update();
}

void CRotator::ChangeQuaternionToLocation(XMFLOAT3 location)
{
	XMFLOAT4 mulQua;
	XMFLOAT3 vec , axis;
	float angle;

	//���������ʒu�ւ̃x�N�g�����v�Z
	LCMath::CalcFloat3FromStartToGoal(mPartner.Location , location , vec);

	//�����x�N�g���ɂ��邽�߂ɐ��K��
	LCMath::CalcFloat3Normalize(vec , vec);

	//�N�H�[�^�j�I���ɕK�v�Ȋp�x���v�Z
	LCMath::CalcFloat3Dot(mPartner.GetForwardVectorWorld() , vec , angle);

	/*
	���ʂ�1(�����_���͂ݏo�邱�Ƃ�����̂�1�ȏ�)�Ȃ�x�N�g�����m�����s�Ȃ̂ŏI��
	-1�ȉ��Ȃ�-1�ɂ���
	*/
	if(angle >= 1.0f)return;
	else if(angle < -1.0f)angle = -1.0f;

	//�p�x�����߂�
	angle = std::acosf(angle);

	//�N�H�[�^�j�I���ɕK�v�Ȏ����v�Z
	LCMath::CalcFloat3Cross(mPartner.GetForwardVectorWorld() , vec , axis);

	//�����S��0�Ȃ玲�������̏�����x�N�g���ɂ���
	if(axis.x == 0 && axis.y == 0 && axis.z == 0)
	{
		axis = mPartner.GetUpwardVectorWorld();
	};

	//�N�H�[�^�j�I���쐬
	LCMath::CreateFromAxisAndAngleToQuaternion(axis , angle , mulQua);

	//�N�H�[�^�j�I���̍���
	LCMath::CalcQuaternionMultiply(mQuaternion , mulQua , mQuaternion);
}

void CRotator::CalcQuaternionToLocation(XMFLOAT3 location , XMFLOAT4& resultQua)
{
	XMFLOAT4 mulQua;
	XMFLOAT3 vec , axis;
	float angle;

	//���������ʒu�ւ̃x�N�g�����v�Z
	LCMath::CalcFloat3FromStartToGoal(mPartner.GetWorldLocation() , location , vec);

	//�����x�N�g���ɂ��邽�߂ɐ��K��
	LCMath::CalcFloat3Normalize(vec , vec);

	//�N�H�[�^�j�I���ɕK�v�Ȋp�x���v�Z
	LCMath::CalcFloat3Dot(mPartner.GetForwardVectorWorld() , vec , angle);

	/*
	���ʂ�1(�����_���͂ݏo�邱�Ƃ�����̂�1�ȏ�)�Ȃ�x�N�g�����m�����s�Ȃ̂ŏI��
	-1�ȉ��Ȃ�-1�ɂ���
	*/
	if(angle >= 1.0f)
	{
		LCMath::IdentityQuaternion(resultQua);

		return;
	}
	else if(angle < -1.0f)angle = -1.0f;

	//�p�x�����߂�
	angle = std::acosf(angle);

	//�N�H�[�^�j�I���ɕK�v�Ȏ����v�Z
	LCMath::CalcFloat3Cross(mPartner.GetForwardVectorWorld() , vec , axis);

	//�����S��0�Ȃ玲�������̏�����x�N�g���ɂ���
	if(axis.x == 0 && axis.y == 0 && axis.z == 0)
	{
		axis = mPartner.GetUpwardVectorWorld();
	};

	//�N�H�[�^�j�I���쐬
	LCMath::CreateFromAxisAndAngleToQuaternion(axis , angle , mulQua);

	//�N�H�[�^�j�I���̍���
	LCMath::CalcQuaternionMultiply(mQuaternion , mulQua , resultQua);
}