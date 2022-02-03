//!
//! @file
//! @brief 戦闘機アクターのヘッダーファイル
//!

#pragma once
#include "GameFramework/Actor/CActor.h"

#include "CPointer.h"

class CParticleSystemComponent;
class CTransform;

//! @brief 戦闘機アクタークラス
class CFighter :public CActor
{
private:
	CPointer& mPointer;			//!< ポインター

	float mSpeed = 50.0f;		//!< 移動速度
	float mSpeedLimitMin;		//!< 速度限界最小値
	float mSpeedLimitMax;		//!< 速度限界最大値

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] owner このアクターを所有するレベル
	//!
	CFighter(ILevel& owner);

	//! @brief 移動
	void Move();

	//!
	//! @brief 回転
	//! @param[in] dire 方向
	//!
	void Rot(int dire);

	//!
	//! @brief 速度変更
	//! @param[in] type タイプ
	//!
	void SpeedChange(int type);

	//! @brief ティック
	void Tick()override;

};