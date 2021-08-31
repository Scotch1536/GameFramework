#include "CColliderManager.h"
#include "../Components/CColliderComponent.h"

CColliderManager& CColliderManager::GetInstance()
{
	static CColliderManager instance;

	return instance;
};

void CColliderManager::AddCollider(CColliderComponent& collider)
{
	mColliders.emplace_back(&collider);

	for(auto& isCache : mIsBefore)
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
	if(mIsBefore.count(caller) == 0)
	{
		mIsBefore[caller] = false;
	}

	//前回の情報があった上でtrueなら前回と変更なし
	if(mIsBefore[caller] == true)return true;

	std::string callerObjType = caller->GetObjectType();
	std::vector<CColliderComponent*> buf;
	for(auto& collider : mColliders)
	{
		//呼び出し元とポインタが一致しないかつオブジェクトタイプがNONEか呼び出し元と一致しないないなら比較対象とする
		if(collider != caller && collider->GetObjectType() == "NONE"||collider->GetObjectType() != callerObjType)
		{
			buf.push_back(collider);
		}
	}
	result = buf;

	mIsBefore[caller] = true;		//前回の情報が最新に更新された

	if(result.size() != 0)return true;		//返す配列がある場合はtrue返す
	else return false;						//ない場合はfalseを返す
}

void CColliderManager::ReleaseCollider(CColliderComponent& collider)
{
	for(auto itr = mColliders.begin(); itr != mColliders.end(); itr++)
	{
		if((*itr) == &collider)
		{
			mColliders.erase(itr);
			mColliders.shrink_to_fit();
			break;
		}
	}

	if(mIsBefore.size() != 0 && mIsBefore.count(&collider) != 0)mIsBefore.erase(&collider);

	if(mIsBefore.size() != 0)
	{
		for(auto& isBefore : mIsBefore)
		{
			isBefore.second = false;
		}
	}
}

void CColliderManager::Update()
{
	if(mColliders.size() != 0)
	{
		for(auto& collider : mColliders)
		{
			collider->ConvertWorldCollider();
		}
	}
}
