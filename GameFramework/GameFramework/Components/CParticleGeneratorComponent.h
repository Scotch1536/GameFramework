#pragma once
#include <random>
#include <vector>
#include <memory>
#include <functional>
#include <DirectXMath.h>

#include "../Actor/CActor.h"
#include "../Transform/CTransform.h"

#include "CComponent.h"

using namespace DirectX;

//�p�[�e�B�N���x�[�X�\����
struct SParticleBase
{
	XMFLOAT3 StartPoint;		//�n�_
	XMFLOAT3 Direction;			//����
};

//���������x�[�X�N���X
class CParticleBaseGenerator
{
protected:
	XMFLOAT3 mBaseAxis;			//��b��

public:
	CParticleBaseGenerator(XMFLOAT3 baseAxis):mBaseAxis(baseAxis) {};

	//��������
	virtual SParticleBase GenerateParticleBase() = 0;
};

//���`���������N���X
class CParticleBaseGeneratorLine :public CParticleBaseGenerator
{
public:
	CParticleBaseGeneratorLine(XMFLOAT3 baseAxis):CParticleBaseGenerator(baseAxis) {};

	SParticleBase GenerateParticleBase()override;
};

//�~�����������N���X
class CParticleBaseGeneratorCone :public CParticleBaseGenerator
{
private:
	std::random_device mRandomSeed;			//�����f�o�C�X
	std::mt19937 mRandomEngine;				//�����A���S���Y��

	std::uniform_real_distribution<float> mRandomGeneratorRadian;		//���W�A���p����������

	float mCentralAngle;		//�p�x

public:
	CParticleBaseGeneratorCone(XMFLOAT3 baseAxis , float centralAngle):CParticleBaseGenerator(baseAxis) , mRandomEngine(mRandomSeed()) ,
		mCentralAngle(centralAngle) , mRandomGeneratorRadian(-1.0f , 1.0f)
	{};

	SParticleBase GenerateParticleBase()override;

	void SetAngle(float angle)
	{
		mCentralAngle = angle;
	}
};

//�p�[�e�B�N�������@�R���|�[�l���g
class CParticleGeneratorComponent :public CComponent
{
	//�p�[�e�B�N���N���X
	class CParticle :public CActor
	{
	private:
		XMFLOAT3 mVelocity;			//�x���V�e�B
		float mLifetime;			//���C�t�^�C���i�b�j

	public:
		CParticle(ILevel& partner , XMFLOAT3 velocity , float lifetime):CActor(partner) ,
			mVelocity(velocity) , mLifetime(lifetime)
		{};

		void Tick()override;

		const XMFLOAT3& GetVelocity()const
		{
			return mVelocity;
		}

		void SetVelocity(XMFLOAT3 velocity)
		{
			mVelocity = velocity;
		}
	};

private:
	CParticle* mParticleBuffer;			//�p�[�e�B�N�����ꎞ�I�ɕێ�����ϐ�

	std::unique_ptr<CParticleBaseGenerator> mParticleBaseGenerator;			//�p�[�e�B�N�������@�̌`��

	std::function<void(CActor&)> mParticleBodyGenerateFunction;				//�p�[�e�B�N���������̎��s�֐�

	XMFLOAT3 mBaseAxis;								//�p�[�e�B�N���V�X�e���̊�b��

	int mGenerationLimit;							//�������E�l(����)
	int mGenerationCounter = 0;						//�����J�E���^�[

	float mParticleLifetime;						//�p�[�e�B�N���̃��C�t�^�C���i�b�j
	float mGenerationGauge = 0.0f;					//�����Q�[�W
	float mIncreasedValueOfGenerationGauge;			//�����Q�[�W�̑����l�i���t���[���j
	float mParticleSpeed;							//�p�[�e�B�N���̑��x�i���t���[���j

	bool mShouldUpdate = true;						//�X�V���ׂ���

	//�X�V
	void Update()override;

	//�p�[�e�B�N������
	void GenerateParticle();

public:
	CTransform Transform;		//�g�����X�t�H�[��

	CParticleGeneratorComponent(CActor& partner , CTransform& parentTrans , std::function<void(CActor&)> particleBodyFunc ,
		float lifetime , float particleSpeed , float generationPerSecond ,
		CParticleBaseGenerator& directionGenerator , int generationLimit = 1000);

	bool SetShouldUpdate(bool flg)
	{
		mShouldUpdate = flg;
	}

};