#include "CCollisionManager.h"
#include "../Components/CCollisionComponent.h"

CCollisionManager& CCollisionManager::GetInstance()
{
	static CCollisionManager instance;

	return instance;
};

void CCollisionManager::AddCollider(CCollisionComponent& collider)
{
	mColliders.emplace_back(&collider);

	for (auto& isCache : mIsBefore)
	{
		isCache.second = false;
	}
}

bool CCollisionManager::GetColliders(CCollisionComponent* caller, std::vector<CCollisionComponent*>& result)
{
	if (mIsBefore.count(caller) == 0)
	{
		mIsBefore[caller] = false;
	}

	if (mIsBefore[caller] == true)return true;

	for (auto& collider : mColliders)
	{
		if (collider != caller)
		{
			result.push_back(collider);
		}
	}

	mIsBefore[caller] = true;

	if (result.size() != 0)return true;		//�Ԃ��z�񂪂���ꍇ��true�Ԃ�
	else return false;						//�Ȃ��ꍇ��false��Ԃ�
}

void CCollisionManager::ReleaseCollider(CCollisionComponent& collider)
{
	for (auto itr = mColliders.begin(); itr != mColliders.end(); itr++)
	{
		if ((*itr) == &collider)
		{
			mColliders.erase(itr);
			mColliders.shrink_to_fit();
			break;
		}
	}
	for (auto isBefore : mIsBefore)
	{
		if (isBefore.first == &collider)
		{
			mIsBefore.erase(&collider);
			break;
		}
	}
}
