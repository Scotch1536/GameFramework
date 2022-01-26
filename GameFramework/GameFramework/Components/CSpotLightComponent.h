#pragma once
#include "CPointLightComponent.h"

//!
//! @file
//! @brief スポットライトコンポーネントのヘッダーファイル
//!

//! @brief スポットライトコンポーネントクラス
class CSpotLightComponent :public CPointLightComponent
{
private:
	XMFLOAT3 mDirection;		//!< 向き
	float mAngle;				//!< 角度（スポットライトの広がり）

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントの所有者
	//! @param[in] parentTrans 親のトランスフォーム
	//! @param[in] attenuation 減衰率
	//! @param[in] direction 向き
	//! @param[in] angle 角度（スポットライトの広がり）
	//! @param[in] location ロケーション
	//!
	CSpotLightComponent(CActor& owner, CTransform& parentTrans,
		XMFLOAT4 attenuation, XMFLOAT3 direction, float angle, XMFLOAT3 location = { 0.0f,0.0f,0.0f });

	const XMFLOAT3 GetDirection()const
	{
		return mDirection;
	}

	const float GetAngle()const
	{
		return mAngle;
	}

	void SetDirection(XMFLOAT3 direction)
	{
		mDirection = direction;

		//ライトマネージャーに通知
		CLightManager::GetInstance().Notice();
	}

	void SetAngle(float angle)
	{
		mAngle = angle;

		//ライトマネージャーに通知
		CLightManager::GetInstance().Notice();
	}

};

