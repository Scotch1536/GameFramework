#pragma once
#include <DirectXMath.h>
#include "CColliderComponent.h"

using namespace DirectX;

class CModelData;
class CBoxMeshComponent;

class CAABBColliderComponent :public CColliderComponent
{
private:
	XMFLOAT3 mLocalMin;
	XMFLOAT3 mLocalMax;

	XMFLOAT3 mWorldMin;
	XMFLOAT3 mWorldMax;

	CBoxMeshComponent* mBoxMesh = nullptr;

	void ConvertWorldCollider()override;

public:
	CAABBColliderComponent(CActor& owner , const CModelData& model , CTransform& parentTrans , bool isMesh = true , int priority = 40);
	CAABBColliderComponent(CActor& owner , XMFLOAT3 min , XMFLOAT3 max , CTransform& parentTrans , bool isMesh = true , int priority = 40);

	void Update()override;
};
