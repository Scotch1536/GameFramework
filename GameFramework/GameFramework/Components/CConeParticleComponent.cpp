#include <random>

#include "CConeParticleComponent.h"
#include "../ExternalCode/dx11mathutil.h"

CConeParticleComponent::CConeParticleComponent(CActor& owner, ILevel& ownerLevel, CTransform& parentTrans, std::function<void(CParticleSystemComponent::Particle&, CTransform&)> func,
	int life, float speed, XMFLOAT3 direction, float qty, float second, float degree)
	:CParticleSystemComponent(owner, ownerLevel, parentTrans, func, life, qty, speed, second), mDegree(degree)
{
	LCMath::CalcFloat3Normalize(direction, mDefaultDirection);
	mDirection = mDefaultDirection;
}

void CConeParticleComponent::Update()
{
	std::random_device rd;
	std::mt19937 mt(rd());

	if (!Transform.Rotation.GetIsSameAngleToBeforeFrame())
	{
		XMFLOAT4X4 rot = Transform.Rotation.GenerateMatrix();
		LCMath::CalcFloat3MultplyMatrix(mDefaultDirection, rot, mDirection);
	}

	mGenerationGauge += mQuantity;
	int numGeneration = mGenerationGauge / 1;

	if (numGeneration >= 1)
	{
		mGenerationGauge -= numGeneration;

		XMFLOAT3 defaultDirection = { 0,1,0 };
		XMFLOAT3 direction;
		XMFLOAT4X4 rotX;
		XMFLOAT4X4 rotZ;
		XMFLOAT4X4 rotMTX;
		XMFLOAT4X4 convertMTX;
		std::uniform_real_distribution urd(-mDegree / 2, mDegree / 2);

		bool shouldConvert = ColcMatrixOfConvert(defaultDirection, convertMTX);

		for (int i = 0; i < numGeneration; ++i)
		{

			DX11MtxRotationAxis({ 1,0,0 }, urd(mt), rotX);
			DX11MtxRotationAxis({ 0,0,1 }, urd(mt), rotZ);
			DX11MtxMultiply(rotMTX, rotX, rotZ);
			DX11Vec3MulMatrix(direction, defaultDirection, rotMTX);

			if (shouldConvert == 1)	LCMath::CalcFloat3MultplyMatrix(direction, convertMTX, direction);
			else if (shouldConvert == 2)	LCMath::CalcFloat3Scalar(direction, -1.f, direction);

			if (shouldConvert)
			{
				//direction = LCMath::CalcFloat3Normalize(direction);
				auto func = [&, direction]
				{
					Particle *particle = new Particle(mLevel, direction, mFunction, mLifeFlame, mSpeed);
					particle->Transform.Location = Transform.GetWorldLocation();
				};
				mOwnerInterface.RequestAddDoBeforeUpdateFunction(func);
			}
			else
			{
				auto func = [&, direction]
				{
					Particle *particle = new Particle(mLevel, direction, mFunction, mLifeFlame, mSpeed);
					particle->Transform.Location = Transform.GetWorldLocation();
				};
				mOwnerInterface.RequestAddDoBeforeUpdateFunction(func);
			}
		}
	}

}

int CConeParticleComponent::ColcMatrixOfConvert(const XMFLOAT3& direction, XMFLOAT4X4& resultMTX)
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
	if (angle >= 1.0f)return 0;
	else if (angle <= -1.0f)
	{
		return 2;
	}

	//�p�x�����߂�
	angle = std::acosf(angle);

	//�O�ςŖ@�����߂�
	//�N�H�[�^�j�I���ɕK�v�Ȏ����v�Z
	LCMath::CalcFloat3Cross(direction, mDirection, axis);

	//�N�H�[�^�j�I���쐬
	LCMath::CreateFromAxisAndAngleToQuaternion(axis, angle, mulQua);

	//�N�H�[�^�j�I������]�s��ɕϊ�
	LCMath::CalcMatrixFromQuaternion(mulQua, resultMTX);

	//��]�s���direction��������direction�ɑ��
	//LCMath::CalcFloat3MultplyMatrix(direction, MTX, direction);

	return 1;
}