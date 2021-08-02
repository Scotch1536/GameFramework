#include <vector>

#include "CVisionComponent.h"
#include "CColliderComponent.h"

#include "..\Library\LCMath.h"
#include "..\Actor\CActor.h"
#include "..\Managers\CColliderManager.h"

CVisionComponent::CVisionComponent(CActor& owner, float length, float angle, int priority)
	:CComponent(owner, priority)
{
	mLength = length;
	mRadian = XMConvertToRadians(angle);
}

void CVisionComponent::Update()
{
	std::vector<CColliderComponent*> colliders;
	CColliderManager::GetInstance().GetColliders(nullptr, colliders);

	std::vector<CComponent*> selfColliders;
	mOwnerInterface.GetActor().GetAllComponents<CColliderComponent>(selfColliders);
	for (auto collider : colliders)
	{
		if (selfColliders.size() != 0)
		{
			bool shouldJudge = true;
			for (const auto& selfCollider : selfColliders)
			{
				if (collider == selfCollider)
				{
					shouldJudge = false;
					break;
				}
			}
			if (!shouldJudge)
			{
				continue;
			}
		}

		float length;
		XMFLOAT3 targetVec;
		XMFLOAT3 selfLoc = mOwnerInterface.GetTransform().GetWorldLocation();
		XMFLOAT3 targetLoc = collider->Transform.GetWorldLocation();
		XMFLOAT3 selfForwardVec = mOwnerInterface.GetTransform().GetForwardVector();

		targetVec.x = selfLoc.x - targetLoc.x;
		targetVec.y = selfLoc.y - targetLoc.y;
		targetVec.z = selfLoc.z - targetLoc.z;

		LCMath::CalcFloat3Length(targetVec, length);
		if (length <= mLength)
		{
			float dot;
			LCMath::CalcFloat3Normalize(targetVec, targetVec);
			LCMath::CalcFloat3Dot(selfForwardVec, targetVec, dot);
			
			std::acos(dot);
			if (dot > mRadian)
			{
				//ì¸ÇÍÇΩä÷êîÇé¿çsÇ∑ÇÈópÇ…Ç∑ÇÈÇ©Ç‡
			}
		}
	}
}
