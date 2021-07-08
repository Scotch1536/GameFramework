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
		AABB,
		SPHERE,
	};

private:
	EType mType;

protected:
	std::vector<CColliderComponent*> mColliders;
	std::unordered_map<CColliderComponent*, SCollideCacheData> mCollideCache;

	std::function<void(CActor&)> mCollideExecuteFunction;		//�Փˎ��ɌĂяo�����֐�

	bool mShouldCompare = true;

	void ExecuteAction(CActor& argument);

	//���_���b�V���̍ő�ŏ������o��
	static void CalcMinMaxOfMeshes(const std::vector<CModelMeshData>& meshes, XMFLOAT3& min, XMFLOAT3& max);

public:
	CTransform Transform;

	CColliderComponent(CActor& owner,CTransform& parentTrans, EType type, int priority = 40);
	virtual ~CColliderComponent();

	virtual void ConvertWorldCollider() = 0;

	void Update() override;

	void BindCollisionAction(std::function<void(CActor&)> action)
	{
		mCollideExecuteFunction = action;
	}

	const EType& GetType()const
	{
		return mType;
	}

};
