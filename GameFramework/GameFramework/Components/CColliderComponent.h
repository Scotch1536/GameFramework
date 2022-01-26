#pragma once
#include <vector>
#include <functional>
#include <unordered_map>

#include "../Transform/CTransform.h"
#include "../Data/CModelMeshData.h"
#include "CComponent.h"

//!
//! @file
//! @brief コライダーコンポーネントのヘッダーファイル
//!

class CTransform;

//! @brief コライドキャッシュデータ構造体
struct SCollideCacheData
{
	bool IsCollide = false;					//!< 当たっているか
	bool IsLastFrameCollide = false;		//!< 最後のフレームが当たっているか
};

//! @brief コライダーコンポーネント
class CColliderComponent :public CComponent
{
public:
	//! @brief コライダータイプ列挙型
	enum class EType
	{
		AABB ,
		SPHERE ,
	};

private:
	EType mType;										//!< コライダータイプ
	std::string mObjectType = "NONE";					//!< オブジェクトタイプ

	std::vector<CColliderComponent*> mColliders;		//!< 自分以外のコライダー

	std::unordered_map<CColliderComponent* , SCollideCacheData> mCollidedCache;			//!< 衝突情報のキャッシュデータ

	std::function<void(CActor&)> mEventAtBeginningCollided;			//!< 衝突開始時イベント
	std::function<void(CActor&)> mEventAtEndCollided;				//!< 衝突終了時イベント

	bool mShouldCompared = true;		//!< 比較すべきか
	bool mShouldUpdate = true;			//!< 更新すべきか

	//! @brief 更新
	void Update() override;

	//!
	//! @brief キャッシュデータの更新
	//! @param[in] target 対象のコライダーコンポーネント
	//! @param[in] isCollided 当たっているか
	//!
	void UpdateCollidedCache(CColliderComponent* targetCollider , bool isCollided);

protected:
	//!
	//! @brief メッシュの頂点の最大最小値を算出する
	//! @param[in] meshes 対象のメッシュ
	//! @param[out] min 最小値の結果
	//! @param[out] max 最大値の結果
	//!
	static void CalcMinMaxOfMeshes(const std::vector<CModelMeshData>& meshes , XMFLOAT3& min , XMFLOAT3& max);

public:
	CTransform Transform;		//!< トランスフォーム

	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントの所有者
	//! @param[in] parentTrans 親のトランスフォーム
	//! @param[in] type コライダーのタイプ
	//! @param[in] priority 優先度
	//!
	CColliderComponent(CActor& owner , CTransform& parentTrans , EType type , int priority = 40);

	//! @brief デストラクタ
	virtual ~CColliderComponent();

	//! @brief コライダーをワールド座標系に変換
	virtual void ConvertWorldCollider() = 0;

	const EType& GetType()const
	{
		return mType;
	}

	const std::string& GetObjectType()const
	{
		return mObjectType;
	}

	void SetObjectType(std::string objType)
	{
		mObjectType = objType;
	}

	void SetShouldUpdate(bool flg)
	{
		mShouldUpdate = flg;
	}

};
