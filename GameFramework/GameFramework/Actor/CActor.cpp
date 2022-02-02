//!
//! @file
//! @brief アクター関連のソースファイル
//!

#include "../Level/CLevel.h"
#include "../Interfaces/IRender.h"
#include "../Managers/CInputManager.h"

#include "CActor.h"

CActor::CActor(ILevel& owner, bool isAffectToPause)
	:CObject("Actor"),
	mOwnerInterface(owner), mIsAffectToPause(isAffectToPause),
	Transform(*this)
{
	//アクター追加
	mOwnerInterface.AddActor(*this);
}

CActor::~CActor()
{
	//入力マネージャーと自身のバインドを切り離す
	CInputManager::GetInstance().ReleaseBindTarget(*this);
}

void CActor::AddComponent(CComponent& component)
{
	int myPriority = component.GetPriority();
	auto itr = this->mComponents.begin();

	for (; itr != this->mComponents.end(); ++itr)
	{
		//引数と同じポインタが見つかった場合終了
		if ((*itr).get() == &component)return;

		//自身の優先度の方が低い場合
		if (myPriority <= (*itr)->GetPriority())
		{
			break;
		}
	}
	//コンポーネントを挿入
	this->mComponents.emplace(itr, &component);
}

void CActor::AddRenderOrder(const SRenderInfo& order)
{
	//描画命令追加
	mRenderOrders.emplace_back(order);
}

void CActor::RequestAddDoBeforeUpdateEvent(std::function<void()> event)
{
	//レベルの更新前実行イベントに追加
	mOwnerInterface.AddDoBeforeUpdateEvent(event);
}

void CActor::Update()
{
	//トランスフォーム更新
	Transform.Update();

	for(auto& component : mComponents)
	{
		//コンポーネント更新
		component->Update();
	}
}

void CActor::Render()
{
	//描画命令のリクエスト
	mOwnerInterface.RegisterRenderOrders(mRenderOrders);
}

void CActor::Destroy()
{
	//アクターの破壊
	mOwnerInterface.DestroyActor(*this);
}