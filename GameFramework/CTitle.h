//!
//! @file
//! @brief タイトルレベルのヘッダーファイル
//!

#pragma once
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Actor/CActor.h"

//! @brief タイトルレベルクラス
class CTitle :public CLevel
{
public:
	using CLevel::CLevel;

	//! @brief 初期化
	void Init()override;

	//! @brief レベルの終了
	void End();
};

