//!
//! @file
//! @brief ライトコンポーネントのソースファイル
//!

#include "CPointLightComponent.h"
#include "CSpotLightComponent.h"

#include "CLightComponent.h"

void CLightComponent::Create(CActor& owner, CTransform& parentTrans, XMFLOAT4 attenuation, XMFLOAT3 location)
{
	//ポイントライト作成
	new CPointLightComponent(owner, parentTrans, attenuation, location);
}

void CLightComponent::Create(CActor& owner, CTransform& parentTrans, XMFLOAT4 attenuation, XMFLOAT3 direction, float angle, XMFLOAT3 location)
{
	//スポットライト作成
	new CSpotLightComponent(owner, parentTrans, attenuation, direction, angle, location);
}
