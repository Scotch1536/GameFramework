#include "../Actor/CActor.h"
#include "../Managers/CColliderManager.h"
#include "../Library/LCCollision.h"

#include "CColliderComponent.h"
#include "CSphereColliderComponent.h"
#include "CAABBColliderComponent.h"

//!
//! @file
//! @brief �R���C�_�[�R���|�[�l���g�̃\�[�X�t�@�C��
//!

CColliderComponent::CColliderComponent(CActor& owner , CTransform& parentTrans , EType type , int priority)
	:CComponent(owner , priority) ,
	mType(type) , mEventAtBeginningCollided(std::bind(&CActor::EventAtBeginCollide , std::ref(owner) , std::placeholders::_1)) ,
	mEventAtEndCollided(std::bind(&CActor::EventAtEndCollide , std::ref(owner) , std::placeholders::_1)) ,
	Transform(owner , parentTrans)
{
	//�R���W�����}�l�[�W���[�Ɏ��g�̃R���C�_�[��ǉ�
	CColliderManager::GetInstance().AddCollider(*this);
}

CColliderComponent::~CColliderComponent()
{
	//�R���W�����}�l�[�W���[�Ɏ��g�̃R���C�_�[��؂藣���Ă��炤
	CColliderManager::GetInstance().ReleaseCollider(*this);
}

void CColliderComponent::Update()
{
	if(!mShouldUpdate)return;

	//��r�Ώۂ̃R���C�_�[����ɓ���Ȃ������ꍇ
	if(!CColliderManager::GetInstance().GetColliders(this , mColliders))mShouldCompared = false;
	else mShouldCompared = true;

	//�e�퓖���蔻�������
	if(mShouldCompared)
	{
		if(mType == EType::AABB)
		{
			//�_�E���L���X�g
			CAABBColliderComponent& thisObj = dynamic_cast<CAABBColliderComponent&>(*this);
			for(auto& collider : mColliders)
			{
				if(collider->GetType() == EType::AABB)
				{
					//�_�E���L���X�g
					CAABBColliderComponent& AABBObj = dynamic_cast<CAABBColliderComponent&>(*collider);

					//�������Ă���Ȃ�
					if(LCCollision::IsCollide(thisObj.GetWorldMin() , thisObj.GetWorldMax() , AABBObj.GetWorldMin() , AABBObj.GetWorldMax()))
					{
						UpdateCollidedCache(collider , true);
					}
					else UpdateCollidedCache(collider , false);
				}
				else if(collider->GetType() == EType::SPHERE)
				{
					//�_�E���L���X�g
					CSphereColliderComponent& sphereObj = dynamic_cast<CSphereColliderComponent&>(*collider);

					//�������Ă���Ȃ�
					if(LCCollision::IsCollide(thisObj.GetWorldMin() , thisObj.GetWorldMax() , sphereObj.GetCenter() , sphereObj.GetWorldRadius()))
					{
						UpdateCollidedCache(collider , true);
					}
					else UpdateCollidedCache(collider , false);
				}
			}
		}
		else if(mType == EType::SPHERE)
		{
			//�_�E���L���X�g
			CSphereColliderComponent& thisObj = dynamic_cast<CSphereColliderComponent&>(*this);
			for(auto& collider : mColliders)
			{
				if(collider->GetType() == EType::AABB)
				{
					//�_�E���L���X�g
					CAABBColliderComponent& AABBObj = dynamic_cast<CAABBColliderComponent&>(*collider);

					//�������Ă���Ȃ�
					if(LCCollision::IsCollide(AABBObj.GetWorldMin() , AABBObj.GetWorldMax() , thisObj.GetCenter() , thisObj.GetWorldRadius()))
					{
						UpdateCollidedCache(collider , true);
					}
					else UpdateCollidedCache(collider , false);
				}
				else if(collider->GetType() == EType::SPHERE)
				{
					//�_�E���L���X�g
					CSphereColliderComponent& Sphereobj = dynamic_cast<CSphereColliderComponent&>(*collider);

					//�������Ă���Ȃ�
					if(LCCollision::IsCollide(thisObj.GetCenter() , thisObj.GetWorldRadius() , Sphereobj.GetCenter() , Sphereobj.GetWorldRadius()))
					{
						UpdateCollidedCache(collider , true);
					}
					else UpdateCollidedCache(collider , false);
				}
			}
		}
	}
}

void CColliderComponent::UpdateCollidedCache(CColliderComponent* targetCollider , bool isCollided)
{
	//�����̃R���C�_�[�R���|�[�l���g���L���b�V���ɑ��݂��Ȃ��Ȃ�
	if(mCollidedCache.count(targetCollider) == 0)
	{
		//�L���b�V�����쐬
		mCollidedCache[targetCollider];	
	}

	//�L���b�V�����X�V�i�������j
	mCollidedCache[targetCollider].IsLastFrameCollide = mCollidedCache[targetCollider].IsCollide;
	mCollidedCache[targetCollider].IsCollide = isCollided;

	//�ՓˊJ�n���Ȃ�
	if(mCollidedCache[targetCollider].IsCollide == true && mCollidedCache[targetCollider].IsLastFrameCollide == false)
	{
		//�ՓˊJ�n�C�x���g���Ă�
		mEventAtBeginningCollided(targetCollider->GetOwner());

		//�^�[�Q�b�g�̃R���C�_�[�����X�V���Ȃ��^�C�v�Ȃ炱���ŃC�x���g���Ăяo��
		if(!targetCollider->mShouldUpdate)targetCollider->mEventAtBeginningCollided(this->GetOwner());
	}
	//�ՓˏI�����Ȃ�
	else if(mCollidedCache[targetCollider].IsCollide == false && mCollidedCache[targetCollider].IsLastFrameCollide == true)
	{
		//�ՓˏI���C�x���g���Ă�
		mEventAtEndCollided(targetCollider->GetOwner());

		//�^�[�Q�b�g�̃R���C�_�[�����X�V���Ȃ��^�C�v�Ȃ炱���ŃC�x���g���Ăяo��
		if(!targetCollider->mShouldUpdate)targetCollider->mEventAtEndCollided(this->GetOwner());
	}
}

void CColliderComponent::CalcMinMaxOfMeshes(const std::vector<CModelMeshData>& meshes , XMFLOAT3& min , XMFLOAT3& max)
{
	for(auto& m : meshes)
	{
		for(auto& v : m.Vertices)
		{
			//�ŏ��ő�l�̍X�V����
			if(min.x > v.Pos.x)	min.x = v.Pos.x;
			else if(max.x < v.Pos.x) max.x = v.Pos.x;

			if(min.y > v.Pos.y)	min.y = v.Pos.y;
			else if(max.y < v.Pos.y) max.y = v.Pos.y;

			if(min.z > v.Pos.z)	min.z = v.Pos.z;
			else if(max.z < v.Pos.z) max.z = v.Pos.z;
		}
	}
}