//!
//! @file
//! @brief AABBコライダーコンポーネントのヘッダーファイル
//!

#pragma once
#include <DirectXMath.h>
#include "CColliderComponent.h"

using namespace DirectX;

class CModelData;
class CBoxMeshComponent;

//! @brief AABBコライダーコンポーネントクラス
class CAABBColliderComponent :public CColliderComponent
{
private:
	XMFLOAT3 mLocalMin;		//!< ローカル座標での最小値
	XMFLOAT3 mLocalMax;		//!< ローカル座標での最大値

	XMFLOAT3 mWorldMin;		//!< ワールド座標での最小値
	XMFLOAT3 mWorldMax;		//!< ワールド座標での最大値

	CBoxMeshComponent* mBoxMesh = nullptr;		//!< デバッグでの視覚化のためのボックスメッシュ

	bool mShouldUpdate = true;					//!< 更新すべきか

	//! @brief ワールド座標空間への変換
	void ConvertWorldCollider()override;

	void SetShouldUpdate(bool flg)
	{
		mShouldUpdate = flg;
	}

public:
	//!
	//! @brief コンストラクタ
	//! @details 3Dモデルをベースにコライダーを作りたい際のコンストラクタ
	//! @param[in] owner このコンポーネントを所有するアクター
	//! @param[in] model コライダーの元になるモデルデータ
	//! @param[in] parentTrans 親のトランスフォーム
	//! @param[in] isMesh メッシュを描画するか
	//! @param[in] priority 優先度
	//!
	CAABBColliderComponent(CActor& owner , const CModelData& model , CTransform& parentTrans , bool isMesh = true , int priority = 40);

	//!
	//! @brief コンストラクタ
	//! @details ベースなしでコライダーを作りたい際のコンストラクタ
	//! @param[in] owner このコンポーネントを所有するアクター
	//! @param[in] parentTrans 親のトランスフォーム
	//! @param[in] isMesh メッシュを描画するか
	//! @param[in] priority 優先度
	//!
	CAABBColliderComponent(CActor& owner , CTransform& parentTrans , bool isMesh = true , int priority = 40);

	XMFLOAT3 GetWorldMin() 
	{ 
		return mWorldMin; 
	}

	XMFLOAT3 GetWorldMax()
	{
		return mWorldMax;
	}

};
