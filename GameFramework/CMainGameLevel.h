//!
//! @file
//! @brief メインゲームレベルのヘッダーファイル
//!

#pragma once
#include "GameFramework/Level/CLevel.h"

//! @brief メインゲームレベルクラス
class CMainGameLevel :public CLevel
{
private:
	float mTime = 60.0f;		//!< 制限時間
	int mScore = 0;				//!< スコア

	bool mIsEnd = false;		//!< 終了かどうか

public:
	using CLevel::CLevel;

	//! @brief 初期化
	void Init()override;

	//! @brief ティック
	void Tick()override;

	//!
	//! @brief 通知
	//! @param[in] actor 通知元のアクター
	void Notice(CActor& actor)override;

};

