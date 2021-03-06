//!
//! @file
//! @brief ポイントライトコンポーネントのソースファイル
//!

#include <functional>
#include "../Actor/CActor.h"

#include "CPointLightComponent.h"

CPointLightComponent::CPointLightComponent(CActor& owner, CTransform& parentTrans, XMFLOAT4 attenuation, XMFLOAT3 location) :
	CLightComponent(owner),
	mAttenuation(attenuation),
	Transform(owner, parentTrans)
{
	mType = EType::POINT;
	Transform.Location = location;

	//トランスフォームの行列更新時実行イベントに自身のメソッドを追加
	Transform.AddEventWhenMatrixUpdate(std::bind(&CLightManager::Notice, std::ref(CLightManager::GetInstance())));
}