#include <Windows.h>
#include <vector>

#include "../Managers/CCollisionManager.h"

#include "CCollisionComponent.h"

CCollisionComponent::CCollisionComponent(CActor& owner , int priority):CComponent(owner , priority)
{
	CCollisionManager::GetInstance().AddCollider(*this);	//自分をコリジョンマネージャーに登録
}

CCollisionComponent::~CCollisionComponent()
{}

void CCollisionComponent::ExecuteAction(CActor& argument)
{
	if(mCollisionAction != nullptr)
	{
		mCollisionAction(argument);
	}
	else
	{
		MessageBox(NULL , "Not Found Function" , "error" , MB_OK);
	}
}

void CCollisionComponent::Update()
{
	if(!CCollisionManager::GetInstance().GetColliders(*this , mColliders))mShouldCompare = false;
}