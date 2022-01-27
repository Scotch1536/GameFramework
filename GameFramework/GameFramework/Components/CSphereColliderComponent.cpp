//!
//! @file
//! @brief �X�t�B�A�R���C�_�[�R���|�[�l���g�̃\�[�X�t�@�C��
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

	//���b�V���̍ŏ��ő�l���Z�o
	CalcMinMaxOfMeshes(model.GetMeshes() , min , max);

	XMFLOAT3 vec;
	float length;

	//�ŏ��ő�l����x�N�g�����Z�o
	LCMath::CalcFloat3FromStartToGoal(min , max , vec);

	//�x�N�g���̒������Z�o
	LCMath::CalcFloat3Length(vec , length);

	//���[�J�����a�Z�o
	mLocalRadius = length / 2.0f;

#ifndef _DEBUG
	isMesh = false;
#endif

	//�X�t�B�A���b�V���쐬
	if(isMesh)mSphereMesh = new CSphereMeshComponent(owner , Transform , { 1.0f,1.0f,1.0f,0.3f } , 50 , mLocalRadius);
}

CSphereColliderComponent::CSphereColliderComponent(CActor& owner , CTransform& parentTrans , bool isMesh , int priority)
	:CColliderComponent(owner , parentTrans , CColliderComponent::EType::SPHERE , priority) ,
	mLocalRadius(0.5f)
{
#ifndef _DEBUG
	isMesh = false;
#endif

	//�X�t�B�A���b�V���쐬
	if(isMesh)mSphereMesh = new CSphereMeshComponent(owner , Transform , { 1.0f,1.0f,1.0f,0.3f } , 50 , mLocalRadius);
}

void CSphereColliderComponent::ConvertWorldCollider()
{
	mCenter = Transform.GetWorldLocation();

	XMFLOAT3 scale = Transform.GetWorldScale();

	//��ԑ傫���X�P�[���̒l���Z�o
	float max = (std::max)({ scale.x,scale.y,scale.z });

	mWorldRadius = mLocalRadius * max;
}
