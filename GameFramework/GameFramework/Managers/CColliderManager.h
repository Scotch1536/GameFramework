//!
//! @file
//! @brief �R���C�_�[�}�l�[�W���[�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <vector>
#include <unordered_map>

class CColliderComponent;

//! @brief �R���C�_�[�}�l�[�W���[�N���X
class CColliderManager
{
private:
	std::vector<CColliderComponent*> mColliders;						//!< �R���C�_�[
	std::unordered_map<CColliderComponent* , bool> mIsCache;			//!< �L���b�V�������邩

	//! @brief �R���X�g���N�^
	CColliderManager() = default;

	//�R�s�[�����[�u�֎~
	CColliderManager(const CColliderManager&) = delete;
	CColliderManager& operator=(const CColliderManager&) = delete;
	CColliderManager(CColliderManager&&) = delete;
	CColliderManager& operator=(CColliderManager&&) = delete;

public:
	//!
	//! @brief �C���X�^���X�擾
	//! @return CColliderManager& �C���X�^���X
	//!
	static CColliderManager& GetInstance();

	//!
	//! @brief �R���C�_�[�ǉ�
	//! @param[in] collider
	//!
	void AddCollider(CColliderComponent& collider);

	//!
	//! @brief �R���C�_�[�擾
	//! @param[in] caller �擾�����N�G�X�g���Ă���R���C�_�[
	//! @param[out] result ���ʂ̃R���C�_�[
	//! @return bool �擾������������
	//!
	bool GetColliders(CColliderComponent* caller, std::vector<CColliderComponent*>& result);

	//!
	//! @brief �R���C�_�[����i�Ǘ��̐؂藣���j
	//! @param[in] collider ��������R���C�_�[
	//!
	void ReleaseCollider(CColliderComponent& collider);

	//! @brief �X�V
	void Update();
};