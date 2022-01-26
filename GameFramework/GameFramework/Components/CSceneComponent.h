#pragma once
#include "../Transform/CTransform.h"
#include "../Actor/CActor.h"

#include "CComponent.h"

//!
//! @file
//! @brief シーンコンポーネントのヘッダーファイル
//!

//! @brief シーンコンポーネントクラス
class CSceneComponent :public CComponent
{
public:
	CTransform Transform;		//!< トランスフォーム

	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントの所有者
	//! @param[in] parentTrans 親のトランスフォーム
	//!
	CSceneComponent(CActor& owner , CTransform& parentTrans):CComponent(owner) , Transform(owner , parentTrans) {};
};