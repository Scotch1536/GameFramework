#pragma once
#include <DirectXMath.h>
#include "CColliderComponent.h"

using namespace DirectX;

class CModelData;

class CAABBComponent :public CColliderComponent
{
private:
	XMFLOAT3 mLocalMin;
	XMFLOAT3 mLocalMax;
	XMFLOAT3 mWorldMin;
	XMFLOAT3 mWorldMax;

	void ConvertWorldCollider() override;

public:
	CAABBComponent(CActor& owner, const CModelData& model, CTransform& parentTrans, int priority = 40);
	CAABBComponent(CActor& owner, XMFLOAT3 min, XMFLOAT3 max, CTransform& parentTrans, int priority = 40);
	~CAABBComponent() {};

	void Update()override;
};
