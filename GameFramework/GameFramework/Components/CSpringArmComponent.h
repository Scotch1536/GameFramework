//!
//! @file
//! @brief スプリングアームコンポーネントのヘッダーファイル
//!

#pragma once
#include <memory>
#include "CComponent.h"

class CTransform;
class CCameraComponent;

//! @brief 接続モード列挙型
enum class ELinkMode
{
	ALL_LINK ,				//!< すべてのトランスフォームを接続
	LOCATION_ONLY_LINK ,	//!< ロケーション情報のみ接続
};

//!< @brief スプリングアームコンポーネントクラス
class CSpringArmComponent :public CComponent
{
private:
	ELinkMode mSyncMode = ELinkMode::ALL_LINK;		//!< 接続モード

	const CTransform& mTargetTransform;				//!< ターゲットのトランスフォーム
	CCameraComponent& mPartnerCamera;				//!< パートナーカメラ

	std::unique_ptr<XMFLOAT4X4> mIdealMatrix;		//!< 理想の行列

	float mLerpTime = 0.0f;							//!< 線形補間のアルファ値が0～1までにかかる秒数
	float mAlpha = 0.0f;							//!< アルファ値
	float mIncrementAlpha = 0.0f;					//!< アルファ値の増加量

	//! @brief 更新
	void Update()override;

	//! @brief アルファ値の増加
	void IncreaseAlpha();

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントを所有するアクター
	//! @param[in] targetTrans ターゲットのトランスフォーム
	//! @param[in] partnerCamera パートナーとなるカメラ
	//! @param[in] linkMode 接続モードカメラ
	//! @param[in] priority 優先度
	//!
	CSpringArmComponent(CActor& owner , const CTransform& targetTrans , CCameraComponent& partnerCamera , ELinkMode linkMode = ELinkMode::ALL_LINK , int priority = 10);

	const ELinkMode& GetLinkMode()
	{
		return mSyncMode;
	}

	void SetLinkMode(ELinkMode mode)
	{
		mSyncMode = mode;
	}

	void SetLerpTime(float time)
	{
		mLerpTime = time;

		//アルファ値の増加量の算出
		mIncrementAlpha = 1.0f / (60.0f * mLerpTime);
	}

};