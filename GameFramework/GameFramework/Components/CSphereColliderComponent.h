//!
//! @file
//! @brief スフィアコライダーコンポーネントのヘッダーファイル
//!

#pragma once
#include <DirectXMath.h>
#include "CColliderComponent.h"

using namespace DirectX;

class CModelData;
class CSphereMeshComponent;

//! @brief スフィアコライダーコンポーネントクラス
class CSphereColliderComponent :public CColliderComponent
{
private:
	XMFLOAT3 mCenter;			//!< 中心座標

	float mLocalRadius;			//!< ローカル半径
	float mWorldRadius;			//!< ワールド半径

	CSphereMeshComponent* mSphereMesh = nullptr;		//!< デバッグでの視覚化のためのスフィアメッシュ

	//! @brief ワールド座標空間への変換
	void ConvertWorldCollider()override;

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
	CSphereColliderComponent(CActor& owner , const CModelData& model , CTransform& parentTrans , bool isMesh = true , int priority = 40);

	//!
	//! @brief コンストラクタ
	//! @details ベースなしでコライダーを作りたい際のコンストラクタ
	//! @param[in] owner このコンポーネントを所有するアクター
	//! @param[in] parentTrans 親のトランスフォーム
	//! @param[in] isMesh メッシュを描画するか
	//! @param[in] priority 優先度
	//!
	CSphereColliderComponent(CActor& owner , CTransform& parentTrans , bool isMesh = true , int priority = 40);

	XMFLOAT3 GetCenter()
	{
		return mCenter;
	}

	float GetWorldRadius()
	{
		return mWorldRadius;
	}

};