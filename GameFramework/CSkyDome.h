//!
//! @file
//! @brief スカイドームアクターのヘッダーファイル
//!

#pragma once
#include "GameFramework/Actor/CActor.h"

//! @brief スカイドームアクタークラス
class CSkyDome :public CActor
{
public:
	//!
	//! @brief コンストラクタ
	//! @param[in] owner このアクターを所有するレベル
	//!
	CSkyDome(ILevel& owner);

};

