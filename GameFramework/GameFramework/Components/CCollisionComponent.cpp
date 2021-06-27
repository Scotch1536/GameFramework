#include <Windows.h>
#include <vector>

#include "../Managers/CCollisionManager.h"

#include "CCollisionComponent.h"

CCollisionComponent::CCollisionComponent(CActor& owner, const CTransform& parentTrans, EType type, int priority) :CComponent(owner, priority),mParentTransform(parentTrans)
{
	CCollisionManager::GetInstance().AddCollider(*this);	//�������R���W�����}�l�[�W���[�ɓo�^
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
	else
	{
		MessageBox(NULL , "Not Found Function" , "error" , MB_OK);
	}
}

void CCollisionComponent::Update()
{
	if(!CCollisionManager::GetInstance().GetColliders(this , mColliders))mShouldCompare = false;
	else mShouldCompare = true;
}