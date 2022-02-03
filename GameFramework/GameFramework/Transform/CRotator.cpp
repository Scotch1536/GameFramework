//!
//!	@file
//!	@brief ���[�e�[�^�[�V�X�e���̃\�[�X�t�@�C��
//!

#include "../Library/LCMath.h"

#include "CRotator.h"
#include "CTransform.h"

CRotator::CRotator(CTransform& partner):mPartner(partner)
{
	LCMath::IdentityQuaternion(mQuaternion);
	LCMath::IdentityQuaternion(mLastFrameQuaternion);
}

void CRotator::Update()
{
	//��v���Ȃ����
	if(!LCMath::CompareFloat4(mQuaternion , mLastFrameQuaternion))
	{
		mLastFrameQuaternion = mQuaternion;

		mIsSameQuaternionToBeforeFrame = false;
	}
	else
	{
		mIsSameQuaternionToBeforeFrame = true;
	}
}

XMFLOAT4X4 CRotator::GenerateMatrix()
{
	XMFLOAT4X4 ansMTX;

	//�N�H�[�^�j�I������s����쐬
	LCMath::TransformFromQuaternionToMatrix(mQuaternion , ansMTX);

	return ansMTX;
}

void CRotator::SetAngle(const XMFLOAT3& angle)
{
	//�����p������]���ɃN�H�[�^�j�I�����Z�o
	LCMath::TransformFromEulerAnglesToQuaternion({ 1.0f,0.0f,0.0f } , { 0.0f , 1.0f , 0.0f } ,
		{ 0.0f,0.0f,1.0f } , angle , mQuaternion);

	mPartner.Update();
}

void CRotator::AddAngleLocal(const XMFLOAT3& angle)
{
	XMFLOAT4 qua;

	//���[�J���̎p������]���ɃN�H�[�^�j�I�����Z�o
	LCMath::TransformFromEulerAnglesToQuaternion(mPartner.GetLocalRightVector() , mPartner.GetLocalUpwardVector() ,
		mPartner.GetLocalForwardVector() , angle , qua);

	//�N�H�[�^�j�I���̍���
	LCMath::CalcQuaternionMultiply(mQuaternion , qua , mQuaternion);

	mPartner.Update();
}

void CRotator::AddAngleWorld(const XMFLOAT3& angle)
{
	XMFLOAT4 qua;

	//���[���h�̎p������]���ɃN�H�[�^�j�I�����Z�o
	LCMath::TransformFromEulerAnglesToQuaternion(mPartner.GetWorldRightVector() , mPartner.GetWorldUpwardVector() ,
		mPartner.GetWorldForwardVector() , angle , qua);

	//�N�H�[�^�j�I���̍���
	LCMath::CalcQuaternionMultiply(mQuaternion , qua , mQuaternion);

	mPartner.Update();
}

void CRotator::ChangeQuaternionToLocation(XMFLOAT3 location)
{
	XMFLOAT4 mulQua;
	XMFLOAT3 vec , axis;
	float angle;

	//���������ʒu�ւ̃x�N�g�����Z�o
	LCMath::CalcFloat3FromStartToEnd(mPartner.Location , location , vec);

	//�����x�N�g���ɂ��邽�߂ɐ��K��
	LCMath::CalcFloat3Normalize(vec , vec);

	//�N�H�[�^�j�I���ɕK�v�Ȋp�x���Z�o
	LCMath::CalcFloat3Dot(mPartner.GetWorldForwardVector() , vec , angle);

	/*
	���ʂ�1(�����_���͂ݏo�邱�Ƃ�����̂�1�ȏ�)�Ȃ�x�N�g�����m�����s�Ȃ̂ŏI��
	-1�ȉ��Ȃ�-1�ɂ���
	*/
	if(angle >= 1.0f)return;
	else if(angle < -1.0f)angle = -1.0f;

	//�p�x�����߂�
	angle = std::acosf(angle);

	//�N�H�[�^�j�I���ɕK�v�Ȏ����Z�o
	LCMath::CalcFloat3Cross(mPartner.GetWorldForwardVector() , vec , axis);

	//�����S��0�Ȃ玲�������̏�����x�N�g���ɂ���
	if(axis.x == 0 && axis.y == 0 && axis.z == 0)
	{
		axis = mPartner.GetWorldUpwardVector();
	};

	//�N�H�[�^�j�I���쐬
	LCMath::CreateFromAxisAndAngleToQuaternion(axis , angle , mulQua);

	//�N�H�[�^�j�I���̍���
	LCMath::CalcQuaternionMultiply(mQuaternion , mulQua , mQuaternion);
}

void CRotator::CalcQuaternionToLocation(XMFLOAT3 location , XMFLOAT4& result)
{
	XMFLOAT4 mulQua;
	XMFLOAT3 vec , axis;
	float angle;

	//���������ʒu�ւ̃x�N�g�����Z�o
	LCMath::CalcFloat3FromStartToEnd(mPartner.GetWorldLocation() , location , vec);

	//�����x�N�g���ɂ��邽�߂ɐ��K��
	LCMath::CalcFloat3Normalize(vec , vec);

	//�N�H�[�^�j�I���ɕK�v�Ȋp�x���Z�o
	LCMath::CalcFloat3Dot(mPartner.GetWorldForwardVector() , vec , angle);

	/*
	���ʂ�1(�����_���͂ݏo�邱�Ƃ�����̂�1�ȏ�)�Ȃ�x�N�g�����m�����s�Ȃ̂ŏI��
	-1�ȉ��Ȃ�-1�ɂ���
	*/
	if(angle >= 1.0f)
	{
		LCMath::IdentityQuaternion(result);

		return;
	}
	else if(angle < -1.0f)angle = -1.0f;

	//�p�x�����߂�
	angle = std::acosf(angle);

	//�N�H�[�^�j�I���ɕK�v�Ȏ����Z�o
	LCMath::CalcFloat3Cross(mPartner.GetWorldForwardVector() , vec , axis);

	//�����S��0�Ȃ玲�������̏�����x�N�g���ɂ���
	if(axis.x == 0 && axis.y == 0 && axis.z == 0)
	{
		axis = mPartner.GetWorldUpwardVector();
	};

	//�N�H�[�^�j�I���쐬
	LCMath::CreateFromAxisAndAngleToQuaternion(axis , angle , mulQua);

	//�N�H�[�^�j�I���̍���
	LCMath::CalcQuaternionMultiply(mQuaternion , mulQua , result);
}