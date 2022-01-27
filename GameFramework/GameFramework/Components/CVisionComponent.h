//!
//! @file
//! @brief 視覚コンポーネントのヘッダーファイル
//!

#pragma once
#include <functional>

#include "CComponent.h"
#include "../Transform/CTransform.h"

class CTransform;
class CActor;

//! @brief 視覚コンポーネントクラス
class CVisionComponent :public CComponent
{
private:
	std::function<void(CActor&)> mEvent;		//!< 見えた時に行われるイベント

	float mDistance;		//!< 視覚の届く距離
	float mBaseAngle;		//!< ベースとなる角度（視野角の半分のラジアン）

	//! @brief 更新
	void Update() override;

public:
	CTransform Transform;		//!< トランスフォーム

	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントを所有するアクター
	//! @param[in] parentTrans 親のトランスフォーム
	//! @param[in] distance 視覚の届く距離
	//! @param[in] fov 視野角
	//! @param[in] event 見えた時に行われるイベント
	//!
	CVisionComponent(CActor& owner, CTransform& parentTrans, float distance, float fov, std::function<void(CActor&)> event);
};