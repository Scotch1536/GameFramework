//!
//! @file
//! @brief アタッチオブジェクトアクターのヘッダーファイル
//!

#pragma once
#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Components/CPrimitiveMeshComponent.h"

//! @brief アタッチオブジェクトアクタークラス
class CAttachObject :public CActor
{
private:
	CPrimitiveMeshComponent<>* mMesh = nullptr;			//!< メッシュ

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] owner このアクターを所有するレベル
	//!
	CAttachObject(ILevel& owner);

	//!
	//! @brief 衝突開始イベント
	//! @param[in] collideActor 当たったアクター
	//!
	void EventAtBeginCollide(CActor& collideActor)override;
};

