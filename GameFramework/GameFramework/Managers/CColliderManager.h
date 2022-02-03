//!
//! @file
//! @brief コライダーマネージャーのヘッダーファイル
//!

#pragma once
#include <vector>
#include <unordered_map>

class CColliderComponent;

//! @brief コライダーマネージャークラス
class CColliderManager
{
private:
	std::vector<CColliderComponent*> mColliders;						//!< コライダー
	std::unordered_map<CColliderComponent* , bool> mIsCache;			//!< キャッシュがあるか

	//! @brief コンストラクタ
	CColliderManager() = default;

	//コピー＆ムーブ禁止
	CColliderManager(const CColliderManager&) = delete;
	CColliderManager& operator=(const CColliderManager&) = delete;
	CColliderManager(CColliderManager&&) = delete;
	CColliderManager& operator=(CColliderManager&&) = delete;

public:
	//!
	//! @brief インスタンス取得
	//! @return CColliderManager& インスタンス
	//!
	static CColliderManager& GetInstance();

	//!
	//! @brief コライダー追加
	//! @param[in] collider
	//!
	void AddCollider(CColliderComponent& collider);

	//!
	//! @brief コライダー取得
	//! @param[in] caller 取得をリクエストしているコライダー
	//! @param[out] result 結果のコライダー
	//! @return bool 取得が成功したか
	//!
	bool GetColliders(CColliderComponent* caller, std::vector<CColliderComponent*>& result);

	//!
	//! @brief コライダー解放（管理の切り離し）
	//! @param[in] collider 解放されるコライダー
	//!
	void ReleaseCollider(CColliderComponent& collider);

	//! @brief 更新
	void Update();
};