#include <Windows.h>
#include <vector>

#include "../Managers/CCollisionManager.h"

#include "CCollisionComponent.h"

CCollisionComponent::CCollisionComponent(CActor& owner, CTransform& parentTrans, EType type, int priority) :CComponent(owner, priority)
{
	parentTrans.AttachTransform(Transform);
	CCollisionManager::GetInstance().AddCollider(*this);	//自分をコリジョンマネージャーに登録
	mType = type;
}

CCollisionComponent::~CCollisionComponent()
{
	CCollisionManager::GetInstance().ReleaseCollider(*this);
}

void CCollisionComponent::ExecuteAction(CActor& argument)
{
	if(mCollisionAction != nullptr)
	{
		mCollisionAction(argument);
	}
}

void CCollisionComponent::Update()
{
	if(!CCollisionManager::GetInstance().GetColliders(this , mColliders))mShouldCompare = false;
	else mShouldCompare = true;
}