#pragma once
#include <vector>

class CCollisionComponent;

class CCollisionManager
{
private:
	std::vector<CCollisionComponent*> mColliders;

	CCollisionManager() = default;

	//コピー＆ムーブ禁止
	CCollisionManager(const CCollisionManager&) = delete;
	CCollisionManager& operator=(const CCollisionManager&) = delete;
	CCollisionManager(CCollisionManager&&) = delete;
	CCollisionManager& operator=(CCollisionManager&&) = delete;
public:
	static CCollisionManager& GetInstance();

	//コリジョンコンポーネントのポインタを追加
	void AddCollider(CCollisionComponent& collider);

	//自分以外のコリジョンコンポーネントのポインタをあげる
	bool GetColliders(const CCollisionComponent& caller, std::vector<CCollisionComponent*>& result);
};