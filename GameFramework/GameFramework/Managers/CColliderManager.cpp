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
	if(mIsBefore.count(caller) == 0)
	{
		mIsBefore[caller] = false;
	}

	if(mIsBefore[caller] == true)return true;

	std::vector<CColliderComponent*> buf;
	for(auto& collider : mColliders)
	{
		if(collider != caller)
		{
			buf.push_back(collider);
		}
	}
	result = buf;

	mIsBefore[caller] = true;

	if(result.size() != 0)return true;		//•Ô‚·”z—ñ‚ª‚ ‚éê‡‚Ítrue•Ô‚·
	else return false;						//‚È‚¢ê‡‚Ífalse‚ð•Ô‚·
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
