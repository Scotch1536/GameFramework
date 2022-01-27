//!
//! @file
//! @brief 視覚コンポーネントのソースファイル
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
	//視野角（弧度法）をラジアンに変換する
	mBaseAngle = XMConvertToRadians(fov / 2.0f);
}

void CVisionComponent::Update()
{
	//コライダーコンポーネントをすべて取得
	std::vector<CColliderComponent*> colliders;
	CColliderManager::GetInstance().GetColliders(nullptr , colliders);

	//自分の所有者のコライダーコンポーネントをすべて取得
	std::vector<CComponent*> selfColliders;
	mOwnerInterface.GetActor().GetAllComponents<CColliderComponent>(selfColliders);

	for(auto collider : colliders)
	{
		bool shouldEvent = false;		//イベントを行うべきか

		//存在していれば
		if(selfColliders.size() != 0)
		{
			bool shouldJudge = true;		//判定すべきか
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

		XMFLOAT3 targetVec;			//ターゲットまでのベクトル
		XMFLOAT3 targetLoc;			//ターゲットのロケーション
		float targetDistance;		//ターゲットまでの距離

		XMFLOAT3 selfLoc = Transform.GetWorldLocation();
		XMFLOAT3 selfForwardVec = Transform.GetForwardVectorWorld();

		XMFLOAT3 keyVec;		//ターゲットの位置から自分の向きベクトルを無限遠に伸ばした線に最短で交わる線のベクトル情報でキーになるベクトル
		float keyVecLength;		//キーベクトルの長さ

		if(collider->GetType() == CColliderComponent::EType::AABB)
		{
			CAABBColliderComponent* aabb = dynamic_cast<CAABBColliderComponent*>(collider);

			//ターゲットのロケーションを代入
			targetLoc = aabb->Transform.GetWorldLocation();

			//最小最大値をターゲットのロケーションからの相対座標として算出
			XMFLOAT3 minLoc = LCMath::CalcFloat3Addition(targetLoc , aabb->GetWorldMin());
			XMFLOAT3 maxLoc = LCMath::CalcFloat3Subtraction(aabb->GetWorldMax() , targetLoc);

			//自分からターゲットまでのベクトルを算出
			LCMath::CalcFloat3FromStartToGoal(selfLoc , targetLoc , targetVec);

			//ターゲットまでのベクトルと自分の向きベクトルとの内積を求め、コサイン（長さ）を算出
			LCMath::CalcFloat3Dot(targetVec , selfForwardVec , keyVecLength);

			//内積で求めた長さを自分の向きベクトルにかけてベクトルを算出、
			//算出したベクトルとターゲットまでのベクトルで減算を行いその二点間のベクトルを算出
			LCMath::CalcFloat3FromStartToGoal(targetVec , LCMath::CalcFloat3Scalar(selfForwardVec , keyVecLength) , keyVec);

			//キーベクトルがAABBの中だったら視界に入ってる判定にする
			if((minLoc.x < keyVec.x && keyVec.x < maxLoc.x) &&
				(minLoc.y < keyVec.y && keyVec.y < maxLoc.y) &&
				(minLoc.z < keyVec.z && keyVec.z < maxLoc.z))
			{
				shouldEvent = true;
			}
			else
			{
				//キーベクトルを更新する
				if(keyVec.x < minLoc.x) keyVec.x = minLoc.x;
				else if(keyVec.x > maxLoc.x) keyVec.x = maxLoc.x;
				else keyVec.x = keyVec.x;

				if(keyVec.y < minLoc.y) keyVec.y = minLoc.y;
				else if(keyVec.y > maxLoc.y) keyVec.y = maxLoc.y;
				else keyVec.y = keyVec.y;

				if(keyVec.z < minLoc.z) keyVec.z = minLoc.z;
				else if(keyVec.z > maxLoc.z) keyVec.z = maxLoc.z;
				else keyVec.z = keyVec.z;

				//ターゲットまでのベクトルを更新する
				LCMath::CalcFloat3Addition(targetVec , keyVec , targetVec);
			}
		}
		if(collider->GetType() == CColliderComponent::EType::SPHERE)
		{
			CSphereColliderComponent* sphere = dynamic_cast<CSphereColliderComponent*>(collider);

			//ターゲットのロケーションを代入
			targetLoc = sphere->GetCenter();

			//自分からターゲットまでのベクトルを算出
			LCMath::CalcFloat3FromStartToGoal(selfLoc , targetLoc , targetVec);

			//ターゲットまでのベクトルと自分の向きベクトルとの内積を求め、コサイン（長さ）を算出
			LCMath::CalcFloat3Dot(targetVec , selfForwardVec , keyVecLength);

			//内積で求めた長さを自分の向きベクトルにかけてベクトルを算出、
			//算出したベクトルとターゲットまでのベクトルで減算を行いその二点間のベクトルを算出
			LCMath::CalcFloat3FromStartToGoal(targetVec , LCMath::CalcFloat3Scalar(selfForwardVec , keyVecLength) , keyVec);

			//キーベクトルがスフィアの中だったら視界に入ってる判定にする
			if(((keyVec.x * keyVec.x) + (keyVec.y * keyVec.y) + (keyVec.z * keyVec.z)) <= (sphere->GetWorldRadius() * sphere->GetWorldRadius()))
			{
				shouldEvent = true;
			}
			else
			{
				//キーベクトルを正規化して向きベクトルにする
				LCMath::CalcFloat3Normalize(keyVec , keyVec);

				//キーベクトルの向きベクトルにターゲットのコリジョンの半径をかけてキーベクトルを更新する
				LCMath::CalcFloat3Scalar(keyVec , sphere->GetWorldRadius() , keyVec);

				//ターゲットまでのベクトルを更新する
				LCMath::CalcFloat3Addition(targetVec , keyVec , targetVec);
			}
		}

		if(!shouldEvent)
		{
			//ターゲットまでの距離を算出
			LCMath::CalcFloat3Length(targetVec , targetDistance);

			//視覚の届く距離にターゲットまでの距離が収まっているなら
			if(targetDistance <= mDistance)
			{
				float targetAngle;		//ターゲットまでの角度

				LCMath::CalcFloat3Normalize(targetVec , targetVec);
				LCMath::CalcFloat3Dot(selfForwardVec , targetVec , targetAngle);

				//ラジアンに変換
				std::acos(targetAngle);

				//ターゲットまでの角度がベースとなる角度に収まるなら
				if(targetAngle <= mBaseAngle || targetAngle <= -mBaseAngle)
				{
					shouldEvent = true;
				}
			}
		}

		if(shouldEvent)
		{
			//イベントを呼び出す
			mEvent(collider->GetOwner());
		}
	}
}
