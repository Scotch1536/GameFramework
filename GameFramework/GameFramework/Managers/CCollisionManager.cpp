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

	for(auto& isCache : mIsBefore)
	{
		isCache.second = false;
	}
}

bool CCollisionManager::GetColliders(const CCollisionComponent& caller , std::vector<CCollisionComponent*>& result)
{
	if(mIsBefore.count(caller) == 0)
	{
		mIsBefore[caller] = false;
	}

	if(mIsBefore[caller] == true)return true;

	for(auto& collider : mColliders)
	{
		if(collider != &caller)
		{
			result.push_back(collider);
		}
	}

	mIsBefore[caller] = true;

	if(result.size() != 0)return true;		//�Ԃ��z�񂪂���ꍇ��true�Ԃ�
	else return false;						//�Ȃ��ꍇ��false��Ԃ�
}