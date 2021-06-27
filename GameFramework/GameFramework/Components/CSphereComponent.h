#pragma once
#include <DirectXMath.h>
#include "CCollisionComponent.h"

using namespace DirectX;

class ModelData;

class CSphereComponent :public CCollisionComponent
{
private:
	float mRadius;
	XMFLOAT3 mWorldPosition;

	void ConvertWorldCollider() override;
	float Distance(const XMFLOAT3& vMax, const XMFLOAT3& vMin);
public:
	CSphereComponent(CActor& owner, const ModelData& model, const CTransform& parentTrans, int priority = 40);
	CSphereComponent(CActor& owner, float radius, const CTransform& parentTrans, int priority = 40);
	~CSphereComponent() {};

	void Update() override;
	
};