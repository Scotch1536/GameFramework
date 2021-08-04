#include <iostream>
#include <vector>

#include "CVisionComponent.h"
#include "CColliderComponent.h"
#include "CAABBColliderComponent.h"
#include "CSphereColliderComponent.h"

#include "..\Library\LCMath.h"
#include "..\Actor\CActor.h"
#include "..\Managers\CColliderManager.h"

CVisionComponent::CVisionComponent(CActor& owner, CTransform& parentTrans, float length, float angle, int priority)
	:CComponent(owner, priority), Transform(parentTrans)
{
	mLength = length;
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
			CSphereColliderComponent* sphere = dynamic_cast<CSphereColliderComponent*>(collider);
			if (sphere == nullptr)
			{
				MessageBox(NULL, "Sphere Upcast failure", "error", MB_OK);
			}
			targetLoc = sphere->GetCenter();
			//自分から相手への向きベクトルを求める
			//相手への向きベクトルと自分の向いてる方向への内積を求める
			float dot = LCMath::CalcFloat3Dot(LCMath::CalcFloat3FromStartToGoal(selfLoc, targetLoc), selfForwardVec);
			//内積で求めた長さに向いてる方向をかけて向きベクトルを求める
			//自分の座標に向きベクトルを足して垂直に交わる座標を求める
			XMFLOAT3 addLoc = LCMath::CalcFloat3Addition(selfLoc, LCMath::CalcFloat3Scalar(selfForwardVec, dot));
			//相手から垂直に交わる座標への向きベクトルを求める
			//相手から垂直に交わる座標への向きベクトルを正規化する
			XMFLOAT3 normalize = LCMath::CalcFloat3Normalize(LCMath::CalcFloat3FromStartToGoal(targetLoc, addLoc));
			//正規化した向きベクトルに相手のコリジョンの半径をかけて自分から一番近い距離を求める
			targetLoc = LCMath::CalcFloat3Scalar(normalize, sphere->GetWorldRadius());

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
			}
		}
	}
}
