#include <Windows.h>
#include <vector>

#include "../Managers/CColliderManager.h"

#include "CColliderComponent.h"

CColliderComponent::CColliderComponent(CActor& owner, CTransform& parentTrans, EType type, int priority) :CComponent(owner, priority)
{
	parentTrans.AttachTransform(Transform);
	CColliderManager::GetInstance().AddCollider(*this);	//自分をコリジョンマネージャーに登録
	mType = type;
}

CColliderComponent::~CColliderComponent()
{
	CColliderManager::GetInstance().ReleaseCollider(*this);
}

void CColliderComponent::ExecuteAction(CActor& argument)
{
	if(mCollisionAction != nullptr)
	{
		mCollisionAction(argument);
	}
}

void CColliderComponent::Update()
{
	if(!CColliderManager::GetInstance().GetColliders(this , mColliders))mShouldCompare = false;
	else mShouldCompare = true;
}