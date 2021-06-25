#pragma once
#include <vector>
#include <unordered_map>

class CCollisionComponent;

class CCollisionManager
{
private:
	std::vector<CCollisionComponent*> mColliders;
	std::unordered_map<CCollisionComponent* , bool> mIsBefore;

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
	bool GetColliders(CCollisionComponent* caller, std::vector<CCollisionComponent*>& result);

	//登録しているコリジョンデータの削除
	void ReleaseCollider(CCollisionComponent& collider);
};