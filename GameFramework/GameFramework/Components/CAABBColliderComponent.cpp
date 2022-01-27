//!
//! @file
//! @brief AABB�R���C�_�[�R���|�[�l���g�̃\�[�X�t�@�C��
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
	//���b�V���̍ŏ��ő�l���Z�o
	CalcMinMaxOfMeshes(model.GetMeshes(), mLocalMin, mLocalMax);

#ifndef _DEBUG
	isMesh = false;
#endif

	//�{�b�N�X���b�V���쐬
	if(isMesh)mBoxMesh = new CBoxMeshComponent(owner , Transform , { 1.0f,1.0f,1.0f,0.3f } , mLocalMin , mLocalMax);
    
	//�g�����X�t�H�[���̍s��X�V���֐��Ɏ��g�̃��\�b�h��ǉ�
	parentTrans.AddMatrixUpdateTimeFunction(std::bind(&CAABBColliderComponent::SetShouldUpdate, std::ref(*this), true));
}

CAABBColliderComponent::CAABBColliderComponent(CActor& owner, CTransform& parentTrans, bool isMesh, int priority)
	:CColliderComponent(owner, parentTrans, CColliderComponent::EType::AABB, priority),
	mLocalMin({ -0.5f,-0.5f,-0.5f }), mLocalMax({ 0.5f,0.5f,0.5f })
{
#ifndef _DEBUG
	isMesh = false;
#endif

	//�{�b�N�X���b�V���쐬
	if(isMesh)mBoxMesh = new CBoxMeshComponent(owner , Transform , { 1.0f,1.0f,1.0f,0.3f } , mLocalMin , mLocalMax);

	//�g�����X�t�H�[���̍s��X�V���֐��Ɏ��g�̃��\�b�h��ǉ�
	parentTrans.AddMatrixUpdateTimeFunction(std::bind(&CAABBColliderComponent::SetShouldUpdate, std::ref(*this), true));
}

void CAABBColliderComponent::ConvertWorldCollider()
{
	if (mShouldUpdate)
	{
		mShouldUpdate = false;

		XMFLOAT4X4 worldMtx = Transform.GetWorldMatrixResult();		//���[���h�ϊ��s��
		std::vector<XMFLOAT3> vertices;

		//���_���̊g���Ə�����
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
			//���[�J�����W�n�ł̒��_�������[���h���W�n�̏��ɕϊ�
			LCMath::CalcFloat3MultplyMatrix(v, worldMtx, v);
		}

		//�ŏ��ő�l���Z�o
		LCMath::CalcFloat3MinMax(vertices, mWorldMin, mWorldMax);
	}
}
