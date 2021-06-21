#include <vector>

#include "CCollisionComponent.h"
#include "CAABBComponent.h"
#include "../Managers/CCollisionManager.h"

CCollisionComponent::CCollisionComponent(CActor& owner, int priority) :CComponent(owner, priority)
{
	CCollisionManager::GetInstance().AddCollider(*this);	//�������R���W�����}�l�[�W���[�ɓo�^
}

void CCollisionComponent::Update()
{
	CCollisionManager::GetInstance().GetColliders(*this, mColliders);
}