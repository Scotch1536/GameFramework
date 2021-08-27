#include "../Library/LCCollision.h"
#include "../Library/LCMath.h"
#include "../Actor/CActor.h"
#include "../Data/CModelData.h"

#include "CAABBColliderComponent.h"
#include "CSphereColliderComponent.h"
#include "CBoxMeshComponent.h"

CAABBColliderComponent::CAABBColliderComponent(CActor& owner , const CModelData& model , CTransform& parentTrans , bool isMesh , int priority)
	:CColliderComponent(owner , parentTrans , CColliderComponent::EType::AABB , priority)
{
	CalcMinMaxOfMeshes(model.GetMeshes() , mLocalMin , mLocalMax);

#ifndef _DEBUG
	isMesh = false;
#endif

	if(isMesh)mBoxMesh = new CBoxMeshComponent(owner , Transform , { 1.0f,1.0f,1.0f,0.3f } , mLocalMin , mLocalMax);
}

CAABBColliderComponent::CAABBColliderComponent(CActor& owner , CTransform& parentTrans , bool isMesh , int priority)
	:CColliderComponent(owner , parentTrans , CColliderComponent::EType::AABB , priority) ,
	mLocalMin({ -0.5f,-0.5f,-0.5f }) , mLocalMax({ 0.5f,0.5f,0.5f })
{
#ifndef _DEBUG
	isMesh = false;
#endif

	if(isMesh)mBoxMesh = new CBoxMeshComponent(owner , Transform , { 1.0f,1.0f,1.0f,0.3f } , mLocalMin , mLocalMax);
}

void CAABBColliderComponent::ConvertWorldCollider()
{
	XMFLOAT3 location = Transform.GetWorldLocation();
	XMFLOAT3 scale = Transform.GetWorldScale();

	mWorldMin.x = (mLocalMin.x * scale.x) + location.x;
	mWorldMin.y = (mLocalMin.y * scale.y) + location.y;
	mWorldMin.z = (mLocalMin.z * scale.z) + location.z;

	mWorldMax.x = (mLocalMax.x * scale.x) + location.x;
	mWorldMax.y = (mLocalMax.y * scale.y) + location.y;
	mWorldMax.z = (mLocalMax.z * scale.z) + location.z;
}
