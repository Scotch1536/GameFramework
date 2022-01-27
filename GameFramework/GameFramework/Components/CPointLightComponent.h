//!
//! @file
//! @brief ポイントライトコンポーネントのヘッダーファイル
//!

#pragma once
#include "CLightComponent.h"

#include "../Transform/CTransform.h"

//! @brief ポイントライトコンポーネントクラス
class CPointLightComponent : public CLightComponent
{
private:
	XMFLOAT4 mAttenuation;		//!< 減衰率

public:
	CTransform Transform;		//!< トランスフォーム

	//!
	//! @brief コンストラクタ
	//! @param[in] owner このコンポーネントを所有するアクター
	//! @param[in] parentTrans 親のトランスフォーム
	//! @param[in] attenuation 減衰率
	//! @param[in] location ロケーション
	//!
	CPointLightComponent(CActor& owner, CTransform& parentTrans,
		XMFLOAT4 attenuation, XMFLOAT3 location = {0.0f,0.0f,0.0f});
	
	const XMFLOAT4 GetAttenuation()const
	{ 
		return mAttenuation; 
	};

	void SetAttenuation(XMFLOAT4 attenuation)
	{
		mAttenuation = attenuation;

		//ライトマネージャーに通知
		CLightManager::GetInstance().Notice();
	}

};