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

			//自分から相手への向きベクトルを求める
			LCMath::CalcFloat3FromStartToGoal(selfLoc, targetLoc, targetVec);
			//相手への向きベクトルと自分の向いてる方向への内積を求める
			LCMath::CalcFloat3Dot(targetVec, selfForwardVec, dot);

			//内積で求めた長さに向いてる方向をかけて向きベクトルを求める
			//相手への向きベクトルから上で求めたベクトルを引いて相手から垂直に交わる座標への向きベクトルを求める
			LCMath::CalcFloat3FromStartToGoal(LCMath::CalcFloat3Scalar(selfForwardVec, dot), targetVec, addLoc);
		}
		if (collider->GetType() == CColliderComponent::EType::SPHERE)
		{
			float dot;
			XMFLOAT3 addLoc;
			XMFLOAT3 normal;

			CSphereColliderComponent* sphere = dynamic_cast<CSphereColliderComponent*>(collider);
			targetLoc = sphere->GetCenter();

			//自分から相手への向きベクトルを求める
			LCMath::CalcFloat3FromStartToGoal(selfLoc, targetLoc, targetVec);
			//相手への向きベクトルと自分の向いてる方向への内積を求める
			LCMath::CalcFloat3Dot(targetVec, selfForwardVec, dot);

			//内積で求めた長さに向いてる方向をかけて向きベクトルを求める
			//相手への向きベクトルから上で求めたベクトルを引いて相手から垂直に交わる座標への向きベクトルを求める
			LCMath::CalcFloat3FromStartToGoal(LCMath::CalcFloat3Scalar(selfForwardVec, dot), targetVec, addLoc);

			//向きベクトルが半径の中だったら視界に入ってる判定にする
			if ((addLoc.x * addLoc.x) + (addLoc.y * addLoc.y) + (addLoc.z * addLoc.z) <= (sphere->GetWorldRadius() * sphere->GetWorldRadius()))
			{
				shouldEvent = true;
			}
			else
			{
				//相手から垂直に交わる座標への向きベクトルを正規化する
				LCMath::CalcFloat3Normalize(addLoc, normal);

				//正規化した向きベクトルに相手のコリジョンの半径をかけて自分から一番近い距離を求める
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

		//入れた関数を実行する用にするかも
		if (shouldEvent && mEvent != nullptr)
		{
			mEvent(collider->GetOwner());
		}
	}
}
