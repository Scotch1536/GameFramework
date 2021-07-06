#pragma once
#include <DirectXMath.h>
#include "CColliderComponent.h"

using namespace DirectX;

class CModelData;
class CSphereMeshComponent;

class CSphereColliderComponent :public CColliderComponent
{
private:
	float mRadius;
	XMFLOAT3 mWorldPosition;
	CSphereMeshComponent* mSphereMesh = nullptr;

	void ConvertWorldCollider() override;
	float Distance(const XMFLOAT3& vMax , const XMFLOAT3& vMin);
public:
	CSphereColliderComponent(CActor& owner , const CModelData& model , CTransform& parentTrans , bool isMesh = true , int priority = 40);
	CSphereColliderComponent(CActor& owner , float radius , CTransform& parentTrans , bool isMesh = true , int priority = 40);
	~CSphereColliderComponent() {};

	void Update() override;

};