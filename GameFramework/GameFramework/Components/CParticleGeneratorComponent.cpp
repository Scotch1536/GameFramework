//!
//! @file
//! @brief �p�[�e�B�N�������R���|�[�l���g�ނ̃\�[�X�t�@�C��
//!

#include "../Actor/CActor.h"
#include "../Library/LCMath.h"
#include "../Managers/CGameManager.h"

#include "CParticleGeneratorComponent.h"

SParticleBase CParticleBaseGeneratorLine::GenerateParticleBase()
{
	SParticleBase result;
	result.Direction = mBaseAxis;
	result.StartPoint = { 0.0f,0.0f,0.0f };

	return result;
}

SParticleBase CParticleBaseGeneratorCone::GenerateParticleBase()
{
	SParticleBase result;

	XMFLOAT4X4 rotMTX;					//��]�s��
	XMFLOAT4 quaternion;				//�N�I�[�^�j�I��
	XMFLOAT3 rotationBaseDirection;		//��]��ƂȂ����
	XMFLOAT3 rotationAxis;				//��]��

	float rotationBaseAngle = mRandomGeneratorRadian(mRandomEngine);			//��]�����邽�߂̉�]�p�x�i���W�A���j
	float rotationAngleRange = XMConvertToRadians(mCentralAngle / 2.0f);		//��������邽�߂̉�]�p�x�͈̔́i���W�A���j

	//��]�p�x�̗���������
	std::uniform_real_distribution<float> rotationAngle(-rotationAngleRange , rotationAngleRange);

	//��]������̌v�Z����
	rotationBaseDirection.x = cosf(rotationBaseAngle);
	rotationBaseDirection.y = 1.0f;
	rotationBaseDirection.z = sinf(rotationBaseAngle);

	LCMath::CalcFloat3Cross(mBaseAxis , rotationBaseDirection , rotationAxis);									//�O�ςŉ�]�����Z�o
	LCMath::CreateFromAxisAndAngleToQuaternion(rotationAxis , rotationAngle(mRandomEngine) , quaternion);		//��]�s��̌��ƂȂ�N�I�[�^�j�I�����Z�o
	LCMath::CalcMatrixFromQuaternion(quaternion , rotMTX);														//��]�s��쐬
	LCMath::CalcFloat3MultplyMatrix(mBaseAxis , rotMTX , result.Direction);										//�������Z�o
	result.StartPoint = { 0.0f,0.0f,0.0f };

	return result;
}

void CParticleGeneratorComponent::CParticle::Tick()
{
	//���C�t�^�C���X�V
	mLifetime -= CGameManager::GetInstance().GetDeltaTime();

	//���C�t�^�C����0�ȉ��Ȃ�f�X�g���C
	if(mLifetime <= 0)
	{
		Destroy();
		return;
	}

	//���P�[�V�����Ƀx���V�e�B�����Z
	LCMath::CalcFloat3Addition(Transform.Location , mVelocity , Transform.Location);
}

CParticleGeneratorComponent::CParticleGeneratorComponent(CActor& partner ,CTransform& parentTrans, std::function<void(CActor&)> particleBodyFunc ,
	float lifetime , float particleSpeed , float generationPerSecond ,
	CParticleBaseGenerator& particleBaseGenerator , int generationLimit):CComponent(partner) ,
	Transform(partner , parentTrans) , mParticleBodyGenerateFunction(particleBodyFunc) ,
	mParticleLifetime(lifetime) , mParticleSpeed(particleSpeed) , mGenerationLimit(generationLimit) ,
	mIncreasedValueOfGenerationGauge(generationPerSecond / 60.0f) , mParticleBaseGenerator(&particleBaseGenerator)
{}

void CParticleGeneratorComponent::Update()
{
	if(!mShouldUpdate)return;

	mGenerationGauge += mIncreasedValueOfGenerationGauge;		//�Q�[�W�ɑ����l�����Z
	int numGeneration = mGenerationGauge / 1;					//�������̎Z�o

	if(numGeneration >= 1)
	{
		mGenerationGauge -= numGeneration;			//�����������Q�[�W�Ɍ��Z

		//�p�[�e�B�N�������̊֐��I�u�W�F�N�g���쐬
		auto generationParticle = [& , numGeneration]
		{
			for(int i = 0; i < numGeneration; ++i)
			{
				if(mGenerationLimit <= mGenerationCounter)break;		//�����J�E���^�[���������E�l�ȏ�Ȃ烋�[�v�𔲂���

				GenerateParticle();										//�p�[�e�B�N������

				mParticleBodyGenerateFunction(*mParticleBuffer);		//�p�[�e�B�N���{�f�B����

				mGenerationCounter++;									//�����J�E���^�[���Z
			}
		};

		//�p�[�e�B�N�������̊֐��I�u�W�F�N�g�����x���̍X�V�O�Ɏ��s����֐��Ƃ��ēo�^
		mOwnerInterface.RequestAddDoBeforeUpdateFunction(generationParticle);
	}
}

void CParticleGeneratorComponent::GenerateParticle()
{
	XMFLOAT3 particleLocation;
	XMFLOAT3 particleVelocity;

	//�p�[�e�B�N���x�[�X����
	SParticleBase particleBase = mParticleBaseGenerator->GenerateParticleBase();

	//���P�[�V�����Z�o
	LCMath::CalcFloat3Addition(Transform.GetWorldLocation() , particleBase.StartPoint , particleLocation);

	//��]�s��쐬����
	XMFLOAT4X4 rotMTX = Transform.GetWorldMatrixResult();		//���ʂ̃}�g���b�N�X�擾
	XMFLOAT3 bufVec;

	bufVec = LCMath::CalcFloat3Normalize({ rotMTX._11,rotMTX._12,rotMTX._13 });
	rotMTX._11 = bufVec.x;
	rotMTX._12 = bufVec.y;
	rotMTX._13 = bufVec.z;

	bufVec = LCMath::CalcFloat3Normalize({ rotMTX._21,rotMTX._22,rotMTX._23 });
	rotMTX._21 = bufVec.x;
	rotMTX._22 = bufVec.y;
	rotMTX._23 = bufVec.z;

	bufVec = LCMath::CalcFloat3Normalize({ rotMTX._31,rotMTX._32,rotMTX._33 });
	rotMTX._31 = bufVec.x;
	rotMTX._32 = bufVec.y;
	rotMTX._33 = bufVec.z;

	rotMTX._41 = 0.0f;
	rotMTX._42 = 0.0f;
	rotMTX._43 = 0.0f;
	rotMTX._44 = 1.0f;

	//���������W�ϊ�
	LCMath::CalcFloat3MultplyMatrix(particleBase.Direction , rotMTX , bufVec);

	//�������x���V�e�B�ɕϊ�
	LCMath::CalcFloat3Scalar(bufVec , mParticleSpeed , particleVelocity);

	//�p�[�e�B�N���쐬
	mParticleBuffer = new CParticle(CGameManager::GetInstance().GetLevelInterface() , particleVelocity , mParticleLifetime);
	mParticleBuffer->Transform.Location = particleLocation;
}