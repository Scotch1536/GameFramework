#pragma once
#include <vector>
#include <unordered_map>

class CColliderComponent;

class CColliderManager
{
private:
	std::vector<CColliderComponent*> mColliders;
	std::unordered_map<CColliderComponent* , bool> mIsBefore;

	CColliderManager() = default;

	//コピー＆ムーブ禁止
	CColliderManager(const CColliderManager&) = delete;
	CColliderManager& operator=(const CColliderManager&) = delete;
	CColliderManager(CColliderManager&&) = delete;
	CColliderManager& operator=(CColliderManager&&) = delete;

public:
	static CColliderManager& GetInstance();

	//コリジョンコンポーネントのポインタを追加
	void AddCollider(CColliderComponent& collider);

	//自分以外のコリジョンコンポーネントのポインタをあげる
	bool GetColliders(CColliderComponent* caller, std::vector<CColliderComponent*>& result);

	//登録しているコリジョンデータの解放
	void ReleaseCollider(CColliderComponent& collider);

	void Update();
};