#pragma once
#include <DirectXMath.h>
#include "CColliderComponent.h"

using namespace DirectX;

class ModelData;

class CSphereColliderComponent :public CColliderComponent
{
private:
	float mRadius;
	XMFLOAT3 mWorldPosition;

	void ConvertWorldCollider() override;
	float Distance(const XMFLOAT3& vMax, const XMFLOAT3& vMin);
public:
	CSphereColliderComponent(CActor& owner, const ModelData& model,CTransform& parentTrans, int priority = 40);
	CSphereColliderComponent(CActor& owner, float radius,CTransform& parentTrans, int priority = 40);
	~CSphereColliderComponent() {};

	void Update() override;
	
};