#pragma once
#include <DirectXMath.h>
#include "CColliderComponent.h"

//!
//! @file
//! @brief AABB�R���C�_�[�R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

using namespace DirectX;

class CModelData;
class CBoxMeshComponent;

//! @brief AABB�R���C�_�[�R���|�[�l���g�N���X
class CAABBColliderComponent :public CColliderComponent
{
private:
	XMFLOAT3 mLocalMin;		//!< ���[�J�����W�ł̍ŏ��l
	XMFLOAT3 mLocalMax;		//!< ���[�J�����W�ł̍ő�l

	XMFLOAT3 mWorldMin;		//!< ���[���h���W�ł̍ŏ��l
	XMFLOAT3 mWorldMax;		//!< ���[���h���W�ł̍ő�l

	CBoxMeshComponent* mBoxMesh = nullptr;		//!< �f�o�b�O�ł̎��o���̂��߂̃{�b�N�X���b�V��

	bool mShouldUpdate = true;					//!< �X�V���ׂ���

	//!
	//! @brief ���[���h���W��Ԃւ̕ϊ�
	//!
	void ConvertWorldCollider()override;

	void SetShouldUpdate(bool flg)
	{
		mShouldUpdate = flg;
	}

public:
	//!
	//! @brief �R���X�g���N�^
	//! @details 3D���f�����x�[�X�ɃR���C�_�[����肽���ۂ̃R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�̏��L��
	//! @param[in] model �R���C�_�[�̌��ɂȂ郂�f���f�[�^
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] isMesh ���b�V����`�悷�邩
	//! @param[in] priority �D��x
	//!
	CAABBColliderComponent(CActor& owner , const CModelData& model , CTransform& parentTrans , bool isMesh = true , int priority = 40);

	//!
	//! @brief �R���X�g���N�^
	//! @details �x�[�X�Ȃ��ŃR���C�_�[����肽���ۂ̃R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�̏��L��
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] isMesh ���b�V����`�悷�邩
	//! @param[in] priority �D��x
	//!
	CAABBColliderComponent(CActor& owner , CTransform& parentTrans , bool isMesh = true , int priority = 40);

	XMFLOAT3 GetWorldMin() 
	{ 
		return mWorldMin; 
	}

	XMFLOAT3 GetWorldMax()
	{
		return mWorldMax;
	}

};
