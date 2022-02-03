//!
//! @file
//! @brief ポインターアクターのヘッダーファイル
//!

#pragma once
#include <memory>
#include "GameFramework/Actor/CActor.h"

class CFighter;

//! @brief ポインターアクタークラス
class CPointer :public CActor
{
private:
	CFighter& mOwner;		//!< 自身を所有する戦闘機

	std::unique_ptr<XMFLOAT3> mInitLocation;		//!< 初期化ロケーション

	float mInitMousePosX;		//!< 初期化マウス座標X
	float mInitMousePosY;		//!< 初期化マウス座標Y
	float mDiffPosX;			//!< 差分座標X
	float mDiffPosY;			//!< 差分座標Y

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] owner このアクターを所有するレベル
	//! @param[in] ownerFighter このアクターを所有する戦闘機
	//!
	CPointer(ILevel& owner , CFighter& ownerFighter);

	//! @brief ティック
	void Tick()override;

};