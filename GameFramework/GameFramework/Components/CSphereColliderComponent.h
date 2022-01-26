#pragma once
#include <DirectXMath.h>
#include "CColliderComponent.h"

//!
//! @file
//! @brief �X�t�B�A�R���C�_�[�R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

using namespace DirectX;

class CModelData;
class CSphereMeshComponent;

//! @brief �X�t�B�A�R���C�_�[�R���|�[�l���g�N���X
class CSphereColliderComponent :public CColliderComponent
{
private:
	XMFLOAT3 mCenter;			//!< ���S���W

	float mLocalRadius;			//!< ���[�J�����a
	float mWorldRadius;			//!< ���[���h���a

	CSphereMeshComponent* mSphereMesh = nullptr;		//!< �f�o�b�O�ł̎��o���̂��߂̃X�t�B�A���b�V��

	//! @brief ���[���h���W��Ԃւ̕ϊ�
	void ConvertWorldCollider()override;

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
	CSphereColliderComponent(CActor& owner , const CModelData& model , CTransform& parentTrans , bool isMesh = true , int priority = 40);

	//!
	//! @brief �R���X�g���N�^
	//! @details �x�[�X�Ȃ��ŃR���C�_�[����肽���ۂ̃R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�̏��L��
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] isMesh ���b�V����`�悷�邩
	//! @param[in] priority �D��x
	//!
	CSphereColliderComponent(CActor& owner , CTransform& parentTrans , bool isMesh = true , int priority = 40);

	XMFLOAT3 GetCenter()
	{
		return mCenter;
	}

	float GetWorldRadius()
	{
		return mWorldRadius;
	}

};