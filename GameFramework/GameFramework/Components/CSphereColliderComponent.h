#pragma once
#include <DirectXMath.h>
#include "CColliderComponent.h"

using namespace DirectX;

class CModelData;
class CSphereMeshComponent;

class CSphereColliderComponent :public CColliderComponent
{
private:
	XMFLOAT3 mCenter;		//���S���W

	float mLocalRadius;			//���[�J�����a
	float mWorldRadius;			//���[���h���a

	CSphereMeshComponent* mSphereMesh = nullptr;

	void ConvertWorldCollider()override;

public:
	CSphereColliderComponent(CActor& owner , const CModelData& model , CTransform& parentTrans , bool isMesh = true , int priority = 40);
	CSphereColliderComponent(CActor& owner , CTransform& parentTrans , bool isMesh = true , int priority = 40);

	XMFLOAT3 GetCenter()
	{
		return mCenter;
	}

	float GetWorldRadius()
	{
		return mWorldRadius;
	}

};