#pragma once
#include <vector>
#include <functional>
#include <unordered_map>

#include "../Transform/CTransform.h"
#include "../Data/CModelMeshData.h"
#include "CComponent.h"

class CTransform;

struct SCollideCacheData
{
	bool IsCollide = false;
	bool IsLastFrameCollide = false;
};

class CColliderComponent :public CComponent
{
public:
	enum class EType
	{
		AABB ,
		SPHERE ,
	};

private:
	EType mType;

	std::vector<CColliderComponent*> mColliders;		//自分以外のコライダー

	std::unordered_map<CColliderComponent* , SCollideCacheData> mCollidedCache;			//衝突情報のキャッシュデータ

	std::function<void(CActor&)> mEventAtBeginCollide;		//衝突開始時に呼び出されるイベント
	std::function<void(CActor&)> mEventAtEndCollide;		//衝突終了時に呼び出されるイベント

	bool mShouldCompared = true;		//比較すべきか

	//キャッシュデータの更新
	void UpdateCollidedCache(CColliderComponent* target , bool isCollided);

protected:
	//頂点メッシュの最大最小を取り出す
	static void CalcMinMaxOfMeshes(const std::vector<CModelMeshData>& meshes , XMFLOAT3& min , XMFLOAT3& max);

public:
	CTransform Transform;

	CColliderComponent(CActor& owner , CTransform& parentTrans , EType type , int priority = 40);
	virtual ~CColliderComponent();

	virtual void ConvertWorldCollider() = 0;

	void Update() override;

	const EType& GetType()const
	{
		return mType;
	}

};
