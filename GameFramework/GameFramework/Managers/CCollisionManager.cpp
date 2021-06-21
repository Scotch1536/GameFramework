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
}

bool CCollisionManager::GetColliders(const CCollisionComponent& caller, std::vector<CCollisionComponent*>& result)
{
	for (auto& collider : mColliders)
	{
		if (collider != &caller)
		{
			result.push_back(collider);
		}
	}
	if (result.size() != 0)return true;		//返す配列がある場合はtrue返す
	else return false;						//ない場合はfalseを返す
}