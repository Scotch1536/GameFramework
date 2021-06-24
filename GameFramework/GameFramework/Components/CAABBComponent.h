#pragma once
#include <DirectXMath.h>
#include "CCollisionComponent.h"

using namespace DirectX;

class ModelData;

class CAABBComponent :public CCollisionComponent
{
private:
	XMFLOAT3 mLocalMin;
	XMFLOAT3 mLocalMax;
	XMFLOAT3 mWorldMin;
	XMFLOAT3 mWorldMax;

	void ConvertWorldCollider() override;

public:
	CAABBComponent(CActor& owner, const ModelData& model, int priority = 40);
	CAABBComponent(CActor& owner, XMFLOAT3 min, XMFLOAT3 max, int priority = 40);
	~CAABBComponent() {};

	void Update() override;
};
