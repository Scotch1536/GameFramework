//!
//! @file
//! @brief AABBコライダーコンポーネントのソースファイル
//!

#include "../Library/LCCollision.h"
#include "../Library/LCMath.h"
#include "../Actor/CActor.h"
#include "../Data/CModelData.h"

#include "CAABBColliderComponent.h"
#include "CSphereColliderComponent.h"
#include "CBoxMeshComponent.h"

CAABBColliderComponent::CAABBColliderComponent(CActor& owner, const CModelData& model, CTransform& parentTrans, bool isMesh, int priority)
	:CColliderComponent(owner, parentTrans, CColliderComponent::EType::AABB, priority)
{
	//メッシュの最小最大値を算出
	CalcMinMaxOfMeshes(model.GetMeshes(), mLocalMin, mLocalMax);

#ifndef _DEBUG
	isMesh = false;
#endif

	//ボックスメッシュ作成
	if(isMesh)mBoxMesh = new CBoxMeshComponent(owner , Transform , { 1.0f,1.0f,1.0f,0.3f } , mLocalMin , mLocalMax);
    
	//トランスフォームの行列更新時イベントに自身のメソッドを追加
	parentTrans.AddEventWhenMatrixUpdate(std::bind(&CAABBColliderComponent::SetShouldUpdate, std::ref(*this), true));
}

CAABBColliderComponent::CAABBColliderComponent(CActor& owner, CTransform& parentTrans, bool isMesh, int priority)
	:CColliderComponent(owner, parentTrans, CColliderComponent::EType::AABB, priority),
	mLocalMin({ -0.5f,-0.5f,-0.5f }), mLocalMax({ 0.5f,0.5f,0.5f })
{
#ifndef _DEBUG
	isMesh = false;
#endif

	//ボックスメッシュ作成
	if(isMesh)mBoxMesh = new CBoxMeshComponent(owner , Transform , { 1.0f,1.0f,1.0f,0.3f } , mLocalMin , mLocalMax);

	//トランスフォームの行列更新時イベントに自身のメソッドを追加
	parentTrans.AddEventWhenMatrixUpdate(std::bind(&CAABBColliderComponent::SetShouldUpdate, std::ref(*this), true));
}

void CAABBColliderComponent::ConvertWorldCollider()
{
	if (mShouldUpdate)
	{
		mShouldUpdate = false;

		XMFLOAT4X4 worldMtx = Transform.GetWorldMatrix();		//ワールド変換行列
		std::vector<XMFLOAT3> vertices;

		//頂点数の拡張と初期化
		vertices.resize(8);
		vertices.at(0) = { mLocalMin.x,mLocalMax.y,mLocalMin.z };
		vertices.at(1) = { mLocalMax.x,mLocalMax.y,mLocalMin.z };
		vertices.at(2) = { mLocalMax.x,mLocalMax.y,mLocalMax.z };
		vertices.at(3) = { mLocalMin.x,mLocalMax.y,mLocalMax.z };
		vertices.at(4) = { mLocalMin.x,mLocalMin.y,mLocalMax.z };
		vertices.at(5) = { mLocalMax.x,mLocalMin.y,mLocalMax.z };
		vertices.at(6) = { mLocalMax.x,mLocalMin.y,mLocalMin.z };
		vertices.at(7) = { mLocalMin.x,mLocalMin.y,mLocalMin.z };

		for (auto& v : vertices)
		{
			//ローカル座標系での頂点情報をワールド座標系の情報に変換
			LCMath::CalcFloat3MultplyMatrix(v, worldMtx, v);
		}

		//最小最大値を算出
		LCMath::CalcFloat3MinMax(vertices, mWorldMin, mWorldMax);
	}
}
