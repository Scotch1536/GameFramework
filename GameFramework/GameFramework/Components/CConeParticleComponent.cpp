#include <random>

#include "CConeParticleComponent.h"
#include "../ExternalCode/dx11mathutil.h"

CConeParticleComponent::CConeParticleComponent(CActor& owner, ILevel& ownerLevel, CTransform& parentTrans, std::function<void(CParticleSystemComponent::Particle&, CTransform&)> func,
	int life, float speed, XMFLOAT3 direction, float qty, float second, float degree)
	:CParticleSystemComponent(owner, ownerLevel, parentTrans, func, life, qty, speed, second), mDegree(degree)
{
	LCMath::CalcFloat3Normalize(direction, mDirection);
}

void CConeParticleComponent::Update()
{
	std::random_device rd;
	std::mt19937 mt(rd());

	mTemporaryDirection.clear();
	if (!Transform.Rotation.GetIsSameAngleToBeforeFrame())
	{
		XMFLOAT4X4 rot = Transform.Rotation.GenerateMatrix();
		LCMath::CalcFloat3MultplyMatrix(mDirection, rot, mDirection);
	}

	if (mQuantity >= 1)
	{
		for (int q = 0; q < mQuantity; q++)
		{
			XMFLOAT3 defaultDirection = { 0,1,0 };
			XMFLOAT3 direction;
			XMFLOAT4X4 rotX;
			XMFLOAT4X4 rotZ;
			XMFLOAT4X4 rotMTX;
			std::uniform_real_distribution urd(-mDegree / 2, mDegree / 2);

			DX11MtxRotationAxis({ 1,0,0 }, urd(mt), rotX);
			DX11MtxRotationAxis({ 0,0,1 }, urd(mt), rotZ);
			DX11MtxMultiply(rotMTX, rotX, rotZ);
			DX11Vec3MulMatrix(direction, defaultDirection, rotMTX);

			if (ConvertDirection(direction))
			{
				direction = LCMath::CalcFloat3Normalize(direction);
				mTemporaryDirection.emplace_back(direction);
				auto func = [&] {new Particle(mLevel, Transform, mTemporaryDirection.back(), mFunction, mLifeFlame, mSpeed); };
				mOwnerInterface.RequestAddDoBeforeUpdateFunction(func);
			}
			else
			{
				auto func = [&] {new Particle(mLevel, Transform, mDirection, mFunction, mLifeFlame, mSpeed); };
				mOwnerInterface.RequestAddDoBeforeUpdateFunction(func);
			}
		}
	}
	else
	{
		if (fmodf(mFrameCount, mQuantity) == 0)
		{
			XMFLOAT3 defaultDirection = { 0,1,0 };
			XMFLOAT3 direction;
			XMFLOAT4X4 rotX;
			XMFLOAT4X4 rotZ;
			XMFLOAT4X4 rotMTX;
			std::uniform_real_distribution urd(-mDegree / 2, mDegree / 2);

			DX11MtxRotationAxis({ 1,0,0 }, urd(mt), rotX);
			DX11MtxRotationAxis({ 0,0,1 }, urd(mt), rotZ);
			DX11MtxMultiply(rotMTX, rotX, rotZ);
			DX11Vec3MulMatrix(direction, defaultDirection, rotMTX);

			if (ConvertDirection(direction))
			{
				direction = LCMath::CalcFloat3Normalize(direction);
				auto func = [&] {new Particle(mLevel, Transform, direction, mFunction, mLifeFlame, mSpeed); };
				mOwnerInterface.RequestAddDoBeforeUpdateFunction(func);
			}
			else
			{
				auto func = [&] {new Particle(mLevel, Transform, mDirection, mFunction, mLifeFlame, mSpeed); };
				mOwnerInterface.RequestAddDoBeforeUpdateFunction(func);
			}
		}
	}
	++mFrameCount;
	if (mFrameCount >= 36000) mFrameCount = 0;
}

bool CConeParticleComponent::ConvertDirection(XMFLOAT3 direction)
{
	XMFLOAT4 mulQua;
	XMFLOAT4X4 MTX;
	XMFLOAT3 axis;
	float angle;

	//�N�H�[�^�j�I���ɕK�v�Ȋp�x���v�Z
	LCMath::CalcFloat3Dot(direction, mDirection, angle);

	/*
	���ʂ�1(�����_���͂ݏo�邱�Ƃ�����̂�1�ȏ�)�Ȃ�x�N�g�����m�����s�Ȃ̂ŏI��
	-1�ȉ��Ȃ�-1�ɂ���
	*/
	if (angle >= 1.0f)return false;
	else if (angle <= -1.0f)
	{
		direction.x *= -1;
		direction.y *= -1;
		direction.z *= -1;

		return true;
	}

	//�p�x�����߂�
	angle = std::acosf(angle);

	//�O�ςŖ@�����߂�
	//�N�H�[�^�j�I���ɕK�v�Ȏ����v�Z
	LCMath::CalcFloat3Cross(direction, mDirection, axis);

	//�N�H�[�^�j�I���쐬
	LCMath::CreateFromAxisAndAngleToQuaternion(axis, angle, mulQua);

	//�N�H�[�^�j�I������]�s��ɕϊ�
	LCMath::CalcMatrixFromQuaternion(mulQua, MTX);

	//��]�s���direction��������direction�ɑ��
	LCMath::CalcFloat3MultplyMatrix(direction, MTX, direction);

	return true;
}