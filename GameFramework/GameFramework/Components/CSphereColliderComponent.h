#pragma once
#include <DirectXMath.h>
#include "CColliderComponent.h"

using namespace DirectX;

class CModelData;
class CSphereMeshComponent;

class CSphereColliderComponent :public CColliderComponent
{
private:
	XMFLOAT3 mWorldLocation;
	float mRadius;

	CSphereMeshComponent* mSphereMesh = nullptr;

	void ConvertWorldCollider()override;

public:
	CSphereColliderComponent(CActor& owner , const CModelData& model , CTransform& parentTrans , bool isMesh = true , int priority = 40);
	CSphereColliderComponent(CActor& owner , float radius , CTransform& parentTrans , bool isMesh = true , int priority = 40);

	XMFLOAT3 GetWorldLocation()
	{
		return mWorldLocation;
	}

	float GetRadius()
	{
		return mRadius;
	}

	void Update()override;

};