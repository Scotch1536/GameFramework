#pragma once
#include <random>
#include <vector>
#include <memory>
#include <functional>
#include <DirectXMath.h>

#include "../Actor/CActor.h"
#include "../Transform/CTransform.h"

#include "CComponent.h"

//!
//! @file
//! @brief �p�[�e�B�N�������R���|�[�l���g�ނ̃w�b�_�[�t�@�C��
//!

using namespace DirectX;

//! @brief �p�[�e�B�N���x�[�X�\����
struct SParticleBase
{
	XMFLOAT3 StartPoint;		//!< �n�_
	XMFLOAT3 Direction;			//!< ����
};

//! @brief �p�[�e�B�N���x�[�X�����N���X
class CParticleBaseGenerator
{
protected:
	XMFLOAT3 mBaseAxis;			//!< ��b��

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] baseAxis ��b��
	//!
	CParticleBaseGenerator(XMFLOAT3 baseAxis):mBaseAxis(baseAxis) {};

	//! @broef �����x�[�X����
	virtual SParticleBase GenerateParticleBase() = 0;
};

//! @brief ���`�p�[�e�B�N���x�[�X�����N���X
class CParticleBaseGeneratorLine :public CParticleBaseGenerator
{
public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] baseAxis ��b��
	//!
	CParticleBaseGeneratorLine(XMFLOAT3 baseAxis):CParticleBaseGenerator(baseAxis) {};

	//! @broef �����x�[�X����
	SParticleBase GenerateParticleBase()override;
};

//! @brief �~���p�[�e�B�N���x�[�X�����N���X
class CParticleBaseGeneratorCone :public CParticleBaseGenerator
{
private:
	std::random_device mRandomSeed;			//!< �����f�o�C�X
	std::mt19937 mRandomEngine;				//!< �����A���S���Y��

	std::uniform_real_distribution<float> mRandomGeneratorRadian;		//!< ���W�A���p����������

	float mCentralAngle;		//!< ���S�p

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] baseAxis ��b��
	//! @param[in] centralAngle ���S�p
	//!
	CParticleBaseGeneratorCone(XMFLOAT3 baseAxis , float centralAngle):CParticleBaseGenerator(baseAxis) , mRandomEngine(mRandomSeed()) ,
		mCentralAngle(centralAngle) , mRandomGeneratorRadian(-1.0f , 1.0f)
	{};

	//! @broef �����x�[�X����
	SParticleBase GenerateParticleBase()override;

	void SetAngle(float angle)
	{
		mCentralAngle = angle;
	}
};

//! @brief �p�[�e�B�N�������R���|�[�l���g
class CParticleGeneratorComponent :public CComponent
{
	//! @brief �p�[�e�B�N���N���X
	class CParticle :public CActor
	{
	private:
		XMFLOAT3 mVelocity;			//!< �x���V�e�B
		float mLifetime;			//!< ���C�t�^�C���i�b�j

	public:
		//!
		//! @brief �R���X�g���N�^
		//! @param[in] partner ���̃A�N�^�[�̏��L���x��
		//! @param[in] velocity �x���V�e�B
		//! @param[in] lifetime ���C�t�^�C��
		//!
		CParticle(ILevel& partner , XMFLOAT3 velocity , float lifetime):CActor(partner) ,
			mVelocity(velocity) , mLifetime(lifetime)
		{};

		//! @brief �e�B�b�N�i���t���[���s���ǉ������j
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
	CParticle* mParticleBuffer;												//!< �p�[�e�B�N�����ꎞ�I�ɕێ�����ϐ�

	std::unique_ptr<CParticleBaseGenerator> mParticleBaseGenerator;			//!< �p�[�e�B�N���x�[�X������

	std::function<void(CActor&)> mParticleBodyGenerateFunction;				//!< �p�[�e�B�N���̖{�̕����̐����֐�

	XMFLOAT3 mBaseAxis;								//!< �p�[�e�B�N��������̊�b��

	int mGenerationLimit;							//!< �������E�l(����)
	int mGenerationCounter = 0;						//!< �����J�E���^�[

	float mParticleLifetime;						//!< �p�[�e�B�N���̃��C�t�^�C���i�b�j
	float mGenerationGauge = 0.0f;					//!< �����Q�[�W
	float mIncreasedValueOfGenerationGauge;			//!< �����Q�[�W�̑����l�i���t���[���j
	float mParticleSpeed;							//!< �p�[�e�B�N���̑��x�i���t���[���j

	bool mShouldUpdate = true;						//!< �X�V���ׂ���

	//! @brief �X�V
	void Update()override;

	//! @brief �p�[�e�B�N������
	void GenerateParticle();

public:
	CTransform Transform;		//!< �g�����X�t�H�[��

	//!
	//! @brief �R���X�g���N�^
	//! @param[in] partner ���̃R���|�[�l���g�̏��L��
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] particleBodyFunc �p�[�e�B�N���̖{�̕����̐����֐��I�u�W�F�N�g
	//! @param[in] lifetime ���C�t�^�C��
	//! @param[in] particleSpeed �p�[�e�B�N���̑��x�i���t���[���j
	//! @param[in] generationPerSecond 1�b�Ԃɐ�������p�[�e�B�N���̐�
	//! @param[in] particleBaseGenerator �p�[�e�B�N���x�[�X������
	//! @param[in] generationLimit �������E�l(����)
	//!
	CParticleGeneratorComponent(CActor& partner , CTransform& parentTrans , std::function<void(CActor&)> particleBodyFunc ,
		float lifetime , float particleSpeed , float generationPerSecond ,
		CParticleBaseGenerator& particleBaseGenerator , int generationLimit = 1000);

	bool SetShouldUpdate(bool flg)
	{
		mShouldUpdate = flg;
	}

};