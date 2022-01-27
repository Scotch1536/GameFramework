//!
//! @file
//! @brief シーンコンポーネントのヘッダーファイル
//!

#pragma once
#include "../Transform/CTransform.h"
#include "../Actor/CActor.h"

#include "CComponent.h"

//! @brief シーンコンポーネントクラス
class CSceneComponent :public CComponent
{
public:
	CTransform Transform;		//!< トランスフォーム

	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントを所有するアクター
	//! @param[in] parentTrans 親のトランスフォーム
	//!
	CSceneComponent(CActor& owner , CTransform& parentTrans):CComponent(owner) , Transform(owner , parentTrans) {};

};