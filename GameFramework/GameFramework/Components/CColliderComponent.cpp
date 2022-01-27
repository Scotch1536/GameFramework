//!
//! @file
//! @brief コライダーコンポーネントのソースファイル
//!

#include "../Actor/CActor.h"
#include "../Managers/CColliderManager.h"
#include "../Library/LCCollision.h"

#include "CColliderComponent.h"
#include "CSphereColliderComponent.h"
#include "CAABBColliderComponent.h"

CColliderComponent::CColliderComponent(CActor& owner , CTransform& parentTrans , EType type , int priority)
	:CComponent(owner , priority) ,
	mType(type) , mEventAtBeginningCollided(std::bind(&CActor::EventAtBeginCollide , std::ref(owner) , std::placeholders::_1)) ,
	mEventAtEndCollided(std::bind(&CActor::EventAtEndCollide , std::ref(owner) , std::placeholders::_1)) ,
	Transform(owner , parentTrans)
{
	//コリジョンマネージャーに自身のコライダーを追加
	CColliderManager::GetInstance().AddCollider(*this);
}

CColliderComponent::~CColliderComponent()
{
	//コリジョンマネージャーに自身のコライダーを切り離してもらう
	CColliderManager::GetInstance().ReleaseCollider(*this);
}

void CColliderComponent::Update()
{
	if(!mShouldUpdate)return;

	//比較対象のコライダーが手に入らなかった場合
	if(!CColliderManager::GetInstance().GetColliders(this , mColliders))mShouldCompared = false;
	else mShouldCompared = true;

	//各種当たり判定を処理
	if(mShouldCompared)
	{
		if(mType == EType::AABB)
		{
			//ダウンキャスト
			CAABBColliderComponent& thisObj = dynamic_cast<CAABBColliderComponent&>(*this);
			for(auto& collider : mColliders)
			{
				if(collider->GetType() == EType::AABB)
				{
					//ダウンキャスト
					CAABBColliderComponent& AABBObj = dynamic_cast<CAABBColliderComponent&>(*collider);

					//当たっているなら
					if(LCCollision::IsCollide(thisObj.GetWorldMin() , thisObj.GetWorldMax() , AABBObj.GetWorldMin() , AABBObj.GetWorldMax()))
					{
						UpdateCollidedCache(collider , true);
					}
					else UpdateCollidedCache(collider , false);
				}
				else if(collider->GetType() == EType::SPHERE)
				{
					//ダウンキャスト
					CSphereColliderComponent& sphereObj = dynamic_cast<CSphereColliderComponent&>(*collider);

					//当たっているなら
					if(LCCollision::IsCollide(thisObj.GetWorldMin() , thisObj.GetWorldMax() , sphereObj.GetCenter() , sphereObj.GetWorldRadius()))
					{
						UpdateCollidedCache(collider , true);
					}
					else UpdateCollidedCache(collider , false);
				}
			}
		}
		else if(mType == EType::SPHERE)
		{
			//ダウンキャスト
			CSphereColliderComponent& thisObj = dynamic_cast<CSphereColliderComponent&>(*this);
			for(auto& collider : mColliders)
			{
				if(collider->GetType() == EType::AABB)
				{
					//ダウンキャスト
					CAABBColliderComponent& AABBObj = dynamic_cast<CAABBColliderComponent&>(*collider);

					//当たっているなら
					if(LCCollision::IsCollide(AABBObj.GetWorldMin() , AABBObj.GetWorldMax() , thisObj.GetCenter() , thisObj.GetWorldRadius()))
					{
						UpdateCollidedCache(collider , true);
					}
					else UpdateCollidedCache(collider , false);
				}
				else if(collider->GetType() == EType::SPHERE)
				{
					//ダウンキャスト
					CSphereColliderComponent& Sphereobj = dynamic_cast<CSphereColliderComponent&>(*collider);

					//当たっているなら
					if(LCCollision::IsCollide(thisObj.GetCenter() , thisObj.GetWorldRadius() , Sphereobj.GetCenter() , Sphereobj.GetWorldRadius()))
					{
						UpdateCollidedCache(collider , true);
					}
					else UpdateCollidedCache(collider , false);
				}
			}
		}
	}
}

void CColliderComponent::UpdateCollidedCache(CColliderComponent* targetCollider , bool isCollided)
{
	//引数のコライダーコンポーネントがキャッシュに存在しないなら
	if(mCollidedCache.count(targetCollider) == 0)
	{
		//キャッシュを作成
		mCollidedCache[targetCollider];	
	}

	//キャッシュを更新（初期化）
	mCollidedCache[targetCollider].IsLastFrameCollide = mCollidedCache[targetCollider].IsCollide;
	mCollidedCache[targetCollider].IsCollide = isCollided;

	//衝突開始時なら
	if(mCollidedCache[targetCollider].IsCollide == true && mCollidedCache[targetCollider].IsLastFrameCollide == false)
	{
		//衝突開始イベントを呼ぶ
		mEventAtBeginningCollided(targetCollider->GetOwner());

		//ターゲットのコライダーがが更新しないタイプならここでイベントを呼び出す
		if(!targetCollider->mShouldUpdate)targetCollider->mEventAtBeginningCollided(this->GetOwner());
	}
	//衝突終了時なら
	else if(mCollidedCache[targetCollider].IsCollide == false && mCollidedCache[targetCollider].IsLastFrameCollide == true)
	{
		//衝突終了イベントを呼ぶ
		mEventAtEndCollided(targetCollider->GetOwner());

		//ターゲットのコライダーがが更新しないタイプならここでイベントを呼び出す
		if(!targetCollider->mShouldUpdate)targetCollider->mEventAtEndCollided(this->GetOwner());
	}
}

void CColliderComponent::CalcMinMaxOfMeshes(const std::vector<CModelMeshData>& meshes , XMFLOAT3& resultMin , XMFLOAT3& resultMax)
{
	for(auto& m : meshes)
	{
		for(auto& v : m.Vertices)
		{
			//最小最大値の更新処理
			if(resultMin.x > v.Pos.x)	resultMin.x = v.Pos.x;
			else if(resultMax.x < v.Pos.x) resultMax.x = v.Pos.x;

			if(resultMin.y > v.Pos.y)	resultMin.y = v.Pos.y;
			else if(resultMax.y < v.Pos.y) resultMax.y = v.Pos.y;

			if(resultMin.z > v.Pos.z)	resultMin.z = v.Pos.z;
			else if(resultMax.z < v.Pos.z) resultMax.z = v.Pos.z;
		}
	}
}