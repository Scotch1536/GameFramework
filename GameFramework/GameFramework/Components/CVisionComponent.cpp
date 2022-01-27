//!
//! @file
//! @brief ���o�R���|�[�l���g�̃\�[�X�t�@�C��
//!

#include <iostream>
#include <vector>

#include "CVisionComponent.h"
#include "CColliderComponent.h"
#include "CAABBColliderComponent.h"
#include "CSphereColliderComponent.h"

#include "..\Library\LCMath.h"
#include "..\Actor\CActor.h"
#include "..\Managers\CColliderManager.h"

CVisionComponent::CVisionComponent(CActor& owner , CTransform& parentTrans , float distance , float fov , std::function<void(CActor&)> event)
	:CComponent(owner , 90) , Transform(owner , parentTrans) , mDistance(distance) , mEvent(event)
{
	//����p�i�ʓx�@�j�����W�A���ɕϊ�����
	mBaseAngle = XMConvertToRadians(fov / 2.0f);
}

void CVisionComponent::Update()
{
	//�R���C�_�[�R���|�[�l���g�����ׂĎ擾
	std::vector<CColliderComponent*> colliders;
	CColliderManager::GetInstance().GetColliders(nullptr , colliders);

	//�����̏��L�҂̃R���C�_�[�R���|�[�l���g�����ׂĎ擾
	std::vector<CComponent*> selfColliders;
	mOwnerInterface.GetActor().GetAllComponents<CColliderComponent>(selfColliders);

	for(auto collider : colliders)
	{
		bool shouldEvent = false;		//�C�x���g���s���ׂ���

		//���݂��Ă����
		if(selfColliders.size() != 0)
		{
			bool shouldJudge = true;		//���肷�ׂ���
			for(const auto& selfCollider : selfColliders)
			{
				if(collider == selfCollider)
				{
					shouldJudge = false;
					break;
				}
			}
			if(!shouldJudge)
			{
				continue;
			}
		}

		XMFLOAT3 targetVec;			//�^�[�Q�b�g�܂ł̃x�N�g��
		XMFLOAT3 targetLoc;			//�^�[�Q�b�g�̃��P�[�V����
		float targetDistance;		//�^�[�Q�b�g�܂ł̋���

		XMFLOAT3 selfLoc = Transform.GetWorldLocation();
		XMFLOAT3 selfForwardVec = Transform.GetForwardVectorWorld();

		XMFLOAT3 keyVec;		//�^�[�Q�b�g�̈ʒu���玩���̌����x�N�g���𖳌����ɐL�΂������ɍŒZ�Ō������̃x�N�g�����ŃL�[�ɂȂ�x�N�g��
		float keyVecLength;		//�L�[�x�N�g���̒���

		if(collider->GetType() == CColliderComponent::EType::AABB)
		{
			CAABBColliderComponent* aabb = dynamic_cast<CAABBColliderComponent*>(collider);

			//�^�[�Q�b�g�̃��P�[�V��������
			targetLoc = aabb->Transform.GetWorldLocation();

			//�ŏ��ő�l���^�[�Q�b�g�̃��P�[�V��������̑��΍��W�Ƃ��ĎZ�o
			XMFLOAT3 minLoc = LCMath::CalcFloat3Addition(targetLoc , aabb->GetWorldMin());
			XMFLOAT3 maxLoc = LCMath::CalcFloat3Subtraction(aabb->GetWorldMax() , targetLoc);

			//��������^�[�Q�b�g�܂ł̃x�N�g�����Z�o
			LCMath::CalcFloat3FromStartToGoal(selfLoc , targetLoc , targetVec);

			//�^�[�Q�b�g�܂ł̃x�N�g���Ǝ����̌����x�N�g���Ƃ̓��ς����߁A�R�T�C���i�����j���Z�o
			LCMath::CalcFloat3Dot(targetVec , selfForwardVec , keyVecLength);

			//���ςŋ��߂������������̌����x�N�g���ɂ����ăx�N�g�����Z�o�A
			//�Z�o�����x�N�g���ƃ^�[�Q�b�g�܂ł̃x�N�g���Ō��Z���s�����̓�_�Ԃ̃x�N�g�����Z�o
			LCMath::CalcFloat3FromStartToGoal(targetVec , LCMath::CalcFloat3Scalar(selfForwardVec , keyVecLength) , keyVec);

			//�L�[�x�N�g����AABB�̒��������王�E�ɓ����Ă锻��ɂ���
			if((minLoc.x < keyVec.x && keyVec.x < maxLoc.x) &&
				(minLoc.y < keyVec.y && keyVec.y < maxLoc.y) &&
				(minLoc.z < keyVec.z && keyVec.z < maxLoc.z))
			{
				shouldEvent = true;
			}
			else
			{
				//�L�[�x�N�g�����X�V����
				if(keyVec.x < minLoc.x) keyVec.x = minLoc.x;
				else if(keyVec.x > maxLoc.x) keyVec.x = maxLoc.x;
				else keyVec.x = keyVec.x;

				if(keyVec.y < minLoc.y) keyVec.y = minLoc.y;
				else if(keyVec.y > maxLoc.y) keyVec.y = maxLoc.y;
				else keyVec.y = keyVec.y;

				if(keyVec.z < minLoc.z) keyVec.z = minLoc.z;
				else if(keyVec.z > maxLoc.z) keyVec.z = maxLoc.z;
				else keyVec.z = keyVec.z;

				//�^�[�Q�b�g�܂ł̃x�N�g�����X�V����
				LCMath::CalcFloat3Addition(targetVec , keyVec , targetVec);
			}
		}
		if(collider->GetType() == CColliderComponent::EType::SPHERE)
		{
			CSphereColliderComponent* sphere = dynamic_cast<CSphereColliderComponent*>(collider);

			//�^�[�Q�b�g�̃��P�[�V��������
			targetLoc = sphere->GetCenter();

			//��������^�[�Q�b�g�܂ł̃x�N�g�����Z�o
			LCMath::CalcFloat3FromStartToGoal(selfLoc , targetLoc , targetVec);

			//�^�[�Q�b�g�܂ł̃x�N�g���Ǝ����̌����x�N�g���Ƃ̓��ς����߁A�R�T�C���i�����j���Z�o
			LCMath::CalcFloat3Dot(targetVec , selfForwardVec , keyVecLength);

			//���ςŋ��߂������������̌����x�N�g���ɂ����ăx�N�g�����Z�o�A
			//�Z�o�����x�N�g���ƃ^�[�Q�b�g�܂ł̃x�N�g���Ō��Z���s�����̓�_�Ԃ̃x�N�g�����Z�o
			LCMath::CalcFloat3FromStartToGoal(targetVec , LCMath::CalcFloat3Scalar(selfForwardVec , keyVecLength) , keyVec);

			//�L�[�x�N�g�����X�t�B�A�̒��������王�E�ɓ����Ă锻��ɂ���
			if(((keyVec.x * keyVec.x) + (keyVec.y * keyVec.y) + (keyVec.z * keyVec.z)) <= (sphere->GetWorldRadius() * sphere->GetWorldRadius()))
			{
				shouldEvent = true;
			}
			else
			{
				//�L�[�x�N�g���𐳋K�����Č����x�N�g���ɂ���
				LCMath::CalcFloat3Normalize(keyVec , keyVec);

				//�L�[�x�N�g���̌����x�N�g���Ƀ^�[�Q�b�g�̃R���W�����̔��a�������ăL�[�x�N�g�����X�V����
				LCMath::CalcFloat3Scalar(keyVec , sphere->GetWorldRadius() , keyVec);

				//�^�[�Q�b�g�܂ł̃x�N�g�����X�V����
				LCMath::CalcFloat3Addition(targetVec , keyVec , targetVec);
			}
		}

		if(!shouldEvent)
		{
			//�^�[�Q�b�g�܂ł̋������Z�o
			LCMath::CalcFloat3Length(targetVec , targetDistance);

			//���o�̓͂������Ƀ^�[�Q�b�g�܂ł̋��������܂��Ă���Ȃ�
			if(targetDistance <= mDistance)
			{
				float targetAngle;		//�^�[�Q�b�g�܂ł̊p�x

				LCMath::CalcFloat3Normalize(targetVec , targetVec);
				LCMath::CalcFloat3Dot(selfForwardVec , targetVec , targetAngle);

				//���W�A���ɕϊ�
				std::acos(targetAngle);

				//�^�[�Q�b�g�܂ł̊p�x���x�[�X�ƂȂ�p�x�Ɏ��܂�Ȃ�
				if(targetAngle <= mBaseAngle || targetAngle <= -mBaseAngle)
				{
					shouldEvent = true;
				}
			}
		}

		if(shouldEvent)
		{
			//�C�x���g���Ăяo��
			mEvent(collider->GetOwner());
		}
	}
}
