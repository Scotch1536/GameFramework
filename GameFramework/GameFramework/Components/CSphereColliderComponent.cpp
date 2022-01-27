//!
//! @file
//! @brief スフィアコライダーコンポーネントのソースファイル
//!

#include <algorithm>

#include "../Library/LCCollision.h"
#include "../Library/LCMath.h"
#include "../Actor/CActor.h"
#include "../Data/CModelData.h"

#include "CAABBColliderComponent.h"
#include "CSphereColliderComponent.h"
#include "CSphereMeshComponent.h"

CSphereColliderComponent::CSphereColliderComponent(CActor& owner , const CModelData& model , CTransform& parentTrans , bool isMesh , int priority)
	:CColliderComponent(owner , parentTrans , CColliderComponent::EType::SPHERE , priority)
{
	XMFLOAT3 min = { 0,0,0 };
	XMFLOAT3 max = { 0,0,0 };

	//メッシュの最小最大値を算出
	CalcMinMaxOfMeshes(model.GetMeshes() , min , max);

	XMFLOAT3 vec;
	float length;

	//最小最大値からベクトルを算出
	LCMath::CalcFloat3FromStartToGoal(min , max , vec);

	//ベクトルの長さを算出
	LCMath::CalcFloat3Length(vec , length);

	//ローカル半径算出
	mLocalRadius = length / 2.0f;

#ifndef _DEBUG
	isMesh = false;
#endif

	//スフィアメッシュ作成
	if(isMesh)mSphereMesh = new CSphereMeshComponent(owner , Transform , { 1.0f,1.0f,1.0f,0.3f } , 50 , mLocalRadius);
}

CSphereColliderComponent::CSphereColliderComponent(CActor& owner , CTransform& parentTrans , bool isMesh , int priority)
	:CColliderComponent(owner , parentTrans , CColliderComponent::EType::SPHERE , priority) ,
	mLocalRadius(0.5f)
{
#ifndef _DEBUG
	isMesh = false;
#endif

	//スフィアメッシュ作成
	if(isMesh)mSphereMesh = new CSphereMeshComponent(owner , Transform , { 1.0f,1.0f,1.0f,0.3f } , 50 , mLocalRadius);
}

void CSphereColliderComponent::ConvertWorldCollider()
{
	mCenter = Transform.GetWorldLocation();

	XMFLOAT3 scale = Transform.GetWorldScale();

	//一番大きいスケールの値を算出
	float max = (std::max)({ scale.x,scale.y,scale.z });

	mWorldRadius = mLocalRadius * max;
}
