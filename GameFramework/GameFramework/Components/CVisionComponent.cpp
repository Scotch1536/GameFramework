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

		/*if (collider->GetType() == CColliderComponent::EType::AABB)
		{
			CAABBColliderComponent* AABB = dynamic_cast<CAABBColliderComponent*>(collider);
			if (AABB == nullptr)
			{
				MessageBox(NULL, "AABB Upcast failure", "error", MB_OK);
			}
			XMFLOAT3 minLoc;
		XMFLOAT3 maxLoc;
			minLoc = AABB->GetWorldMin();
			maxLoc = AABB->GetWorldMax();

		}*/
		if (collider->GetType() == CColliderComponent::EType::SPHERE)
		{
			float dot;
			XMFLOAT3 addLoc;
			XMFLOAT3 normal;

			CSphereColliderComponent* sphere = dynamic_cast<CSphereColliderComponent*>(collider);
			targetLoc = sphere->GetCenter();

			//自分から相手への向きベクトルを求める
			//相手への向きベクトルと自分の向いてる方向への内積を求める
			LCMath::CalcFloat3Dot(LCMath::CalcFloat3FromStartToGoal(selfLoc, targetLoc), selfForwardVec, &dot);

			//内積で求めた長さに向いてる方向をかけて向きベクトルを求める
			//自分の座標に向きベクトルを足して垂直に交わる座標を求める
			LCMath::CalcFloat3Addition(selfLoc, LCMath::CalcFloat3Scalar(selfForwardVec, dot), &addLoc);

			//相手から垂直に交わる座標への向きベクトルを求める
			//相手から垂直に交わる座標への向きベクトルを正規化する
			LCMath::CalcFloat3Normalize(LCMath::CalcFloat3FromStartToGoal(targetLoc, addLoc), &normal);

			//正規化した向きベクトルに相手のコリジョンの半径をかけて自分から一番近い距離を求める
			LCMath::CalcFloat3Scalar(normal, sphere->GetWorldRadius(), &targetLoc);

		}

		targetVec.x = selfLoc.x - targetLoc.x;
		targetVec.y = selfLoc.y - targetLoc.y;
		targetVec.z = selfLoc.z - targetLoc.z;

		LCMath::CalcFloat3Length(targetVec, &length);
		if (length <= mLength)
		{
			float dot;
			LCMath::CalcFloat3Normalize(targetVec, &targetVec);
			LCMath::CalcFloat3Dot(selfForwardVec, targetVec, &dot);

			std::acos(dot);
			if (dot > mRadian)
			{
				//入れた関数を実行する用にするかも
				if (mEvent != nullptr)
				{
					mEvent(collider->GetOwner());
				}
			}
		}
	}
}
