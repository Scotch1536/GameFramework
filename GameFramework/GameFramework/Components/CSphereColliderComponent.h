#pragma once
#include <DirectXMath.h>
#include "CColliderComponent.h"

using namespace DirectX;

class CModelData;
class CSphereMeshComponent;

class CSphereColliderComponent :public CColliderComponent
{
private:
	XMFLOAT3 mCenter;		//中心座標

	float mLocalRadius;			//ローカル半径
	float mWorldRadius;			//ワールド半径

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