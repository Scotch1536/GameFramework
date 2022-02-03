//!
//! @file
//! @brief コライダーマネージャーのソースファイル
//!

#include "CColliderManager.h"
#include "../Components/CColliderComponent.h"

CColliderManager& CColliderManager::GetInstance()
{
	static CColliderManager instance;

	return instance;
};

void CColliderManager::AddCollider(CColliderComponent& collider)
{
	auto sameCollider = std::find(mColliders.begin() , mColliders.end() , &collider);

	//同じコライダーがあれば終了
	if(sameCollider != mColliders.end())return;

	mColliders.emplace_back(&collider);

	//キャッシュを更新しなければならないためフラグをすべてfalseにする
	for(auto& isCache : mIsCache)
	{
		isCache.second = false;
	}
}

bool CColliderManager::GetColliders(CColliderComponent* caller , std::vector<CColliderComponent*>& result)
{
	//呼び出し元がなければ全てのコライダーを返す
	if(caller == nullptr)
	{
		result = mColliders;
		return true;
	}

	//前回の情報がなければ作る
	if(mIsCache.count(caller) == 0)
	{
		mIsCache[caller] = false;
	}

	//前回の情報があった上でtrueなら前回と変更なし
	if(mIsCache[caller] == true)return true;

	std::string callerObjType = caller->GetObjectType();
	std::vector<CColliderComponent*> buf;
	for(auto& collider : mColliders)
	{
		//呼び出し元とポインタが一致しないかつオブジェクトタイプがNONEか呼び出し元と一致しないないなら比較対象とする
		if(collider != caller && collider->GetObjectType() == "NONE" || collider->GetObjectType() != callerObjType)
		{
			buf.push_back(collider);
		}
	}
	result = buf;

	mIsCache[caller] = true;		//前回の情報が最新に更新された

	if(result.size() != 0)return true;		//返す配列がある場合はtrue返す
	else return false;						//ない場合はfalseを返す
}

void CColliderManager::ReleaseCollider(CColliderComponent& collider)
{
	//存在しないなら終了
	if(mIsCache.size() == 0)return;

	for(auto itr = mColliders.begin(); itr != mColliders.end(); itr++)
	{
		if((*itr) == &collider)
		{
			mColliders.erase(itr);
			mColliders.shrink_to_fit();
			break;
		}
	}

	if(mIsCache.count(&collider) != 0)mIsCache.erase(&collider);

	for(auto& isBefore : mIsCache)
	{
		isBefore.second = false;
	}
}

void CColliderManager::Update()
{
	if(mColliders.size() != 0)
	{
		for(auto& collider : mColliders)
		{
			//ワールド座標系のコライダー情報に変換
			collider->ConvertWorldCollider();
		}
	}
}
