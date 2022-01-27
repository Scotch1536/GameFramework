//!
//! @file
//! @brief コンポーネントのソースファイル
//!

#include "../Actor/CActor.h"

#include "CComponent.h"

CComponent::CComponent(CActor& owner , int priority):mPriority(priority),mOwnerInterface(owner)
{
	//所有者のアクターに自身のコンポーネントを追加してもらう
	mOwnerInterface.AddComponent(*this);
}

CComponent::~CComponent() {}

CActor& CComponent::GetOwner()const
{
	return mOwnerInterface.GetActor();
}