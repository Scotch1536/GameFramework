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
	std::string mObjectType = "NONE";

	std::vector<CColliderComponent*> mColliders;		//�����ȊO�̃R���C�_�[

	std::unordered_map<CColliderComponent* , SCollideCacheData> mCollidedCache;			//�Փˏ��̃L���b�V���f�[�^

	std::function<void(CActor&)> mEventAtBeginningCollided;		//�ՓˊJ�n���ɌĂяo�����C�x���g
	std::function<void(CActor&)> mEventAtEndCollided;			//�ՓˏI�����ɌĂяo�����C�x���g

	bool mShouldCompared = true;		//��r���ׂ���
	bool mIsUpdate = true;				//�X�V���邩

	//�L���b�V���f�[�^�̍X�V
	void UpdateCollidedCache(CColliderComponent* target , bool isCollided);

	void Update() override;

protected:
	//���_���b�V���̍ő�ŏ������o��
	static void CalcMinMaxOfMeshes(const std::vector<CModelMeshData>& meshes , XMFLOAT3& min , XMFLOAT3& max);

public:
	CTransform Transform;

	CColliderComponent(CActor& owner , CTransform& parentTrans , EType type , int priority = 40);
	virtual ~CColliderComponent();

	virtual void ConvertWorldCollider() = 0;

	const EType& GetType()const
	{
		return mType;
	}

	const std::string& GetObjectType()const
	{
		return mObjectType;
	}

	void SetObjectType(std::string objType)
	{
		mObjectType = objType;
	}

	void SetIsUpdate(bool flg)
	{
		mIsUpdate = flg;
	}

};
