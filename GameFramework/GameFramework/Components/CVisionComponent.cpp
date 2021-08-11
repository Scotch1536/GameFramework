#include <iostream>
#include <vector>

#include "CVisionComponent.h"
#include "CColliderComponent.h"
#include "CAABBColliderComponent.h"
#include "CSphereColliderComponent.h"

#include "..\Library\LCMath.h"
#include "..\Actor\CActor.h"
#include "..\Managers\CColliderManager.h"

CVisionComponent::CVisionComponent(CActor& owner, CTransform& parentTrans, float length, float angle, std::function<void(CActor&)> event, int priority)
	:CComponent(owner, priority), Transform(parentTrans), mLength(length), mEvent(event)
{
	mRadian = XMConvertToRadians(angle);
}

void CVisionComponent::Update()
{
	std::vector<CColliderComponent*> colliders;
	CColliderManager::GetInstance().GetColliders(nullptr, colliders);

	std::vector<CComponent*> selfColliders;
	mOwnerInterface.GetActor().GetAllComponents<CColliderComponent>(selfColliders);
	for (auto collider : colliders)
	{
		bool shouldEvent = false;
		if (selfColliders.size() != 0)
		{
			bool shouldJudge = true;
			for (const auto& selfCollider : selfColliders)
			{
				if (collider == selfCollider)
				{
					shouldJudge = false;
					break;
				}
			}
			if (!shouldJudge)
			{
				continue;
			}
		}

		float length;
		XMFLOAT3 targetVec;
		XMFLOAT3 targetLoc;
		XMFLOAT3 selfLoc = Transform.GetWorldLocation();
		XMFLOAT3 selfForwardVec = Transform.GetForwardVector();

		if (collider->GetType() == CColliderComponent::EType::AABB)
		{
			float dot;
			XMFLOAT3 minLoc;
			XMFLOAT3 maxLoc;
			XMFLOAT3 addLoc;
			
			CAABBColliderComponent* AABB = dynamic_cast<CAABBColliderComponent*>(collider);
			targetLoc = AABB->Transform.GetWorldLocation();
			minLoc = AABB->GetWorldMin();
			maxLoc = AABB->GetWorldMax();

			//�������瑊��ւ̌����x�N�g�������߂�
			LCMath::CalcFloat3FromStartToGoal(selfLoc, targetLoc, targetVec);
			//����ւ̌����x�N�g���Ǝ����̌����Ă�����ւ̓��ς����߂�
			LCMath::CalcFloat3Dot(targetVec, selfForwardVec, dot);

			//���ςŋ��߂������Ɍ����Ă�����������Č����x�N�g�������߂�
			//����ւ̌����x�N�g�������ŋ��߂��x�N�g���������đ��肩�琂���Ɍ������W�ւ̌����x�N�g�������߂�
			LCMath::CalcFloat3FromStartToGoal(LCMath::CalcFloat3Scalar(selfForwardVec, dot), targetVec, addLoc);
		}
		if (collider->GetType() == CColliderComponent::EType::SPHERE)
		{
			float dot;
			XMFLOAT3 addLoc;
			XMFLOAT3 normal;

			CSphereColliderComponent* sphere = dynamic_cast<CSphereColliderComponent*>(collider);
			targetLoc = sphere->GetCenter();

			//�������瑊��ւ̌����x�N�g�������߂�
			LCMath::CalcFloat3FromStartToGoal(selfLoc, targetLoc, targetVec);
			//����ւ̌����x�N�g���Ǝ����̌����Ă�����ւ̓��ς����߂�
			LCMath::CalcFloat3Dot(targetVec, selfForwardVec, dot);

			//���ςŋ��߂������Ɍ����Ă�����������Č����x�N�g�������߂�
			//����ւ̌����x�N�g�������ŋ��߂��x�N�g���������đ��肩�琂���Ɍ������W�ւ̌����x�N�g�������߂�
			LCMath::CalcFloat3FromStartToGoal(LCMath::CalcFloat3Scalar(selfForwardVec, dot), targetVec, addLoc);

			//�����x�N�g�������a�̒��������王�E�ɓ����Ă锻��ɂ���
			if ((addLoc.x * addLoc.x) + (addLoc.y * addLoc.y) + (addLoc.z * addLoc.z) <= (sphere->GetWorldRadius() * sphere->GetWorldRadius()))
			{
				shouldEvent = true;
			}
			else
			{
				//���肩�琂���Ɍ������W�ւ̌����x�N�g���𐳋K������
				LCMath::CalcFloat3Normalize(addLoc, normal);

				//���K�����������x�N�g���ɑ���̃R���W�����̔��a�������Ď��������ԋ߂����������߂�
				LCMath::CalcFloat3Scalar(normal, sphere->GetWorldRadius(), targetLoc);
			}
		}

		if (!shouldEvent)
		{
			LCMath::CalcFloat3Length(targetVec, length);
			if (length <= mLength)
			{
				float dot;
				LCMath::CalcFloat3Normalize(targetVec, targetVec);
				LCMath::CalcFloat3Dot(selfForwardVec, targetVec, dot);

				std::acos(dot);
				if (dot > mRadian)
				{
					shouldEvent = true;
				}
			}
		}

		//���ꂽ�֐������s����p�ɂ��邩��
		if (shouldEvent && mEvent != nullptr)
		{
			mEvent(collider->GetOwner());
		}
	}
}
