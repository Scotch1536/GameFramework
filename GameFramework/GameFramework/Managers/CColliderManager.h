#pragma once
#include <vector>
#include <unordered_map>

class CColliderComponent;

class CColliderManager
{
private:
	std::vector<CColliderComponent*> mColliders;
	std::unordered_map<CColliderComponent* , bool> mIsBefore;

	CColliderManager() = default;

	//�R�s�[�����[�u�֎~
	CColliderManager(const CColliderManager&) = delete;
	CColliderManager& operator=(const CColliderManager&) = delete;
	CColliderManager(CColliderManager&&) = delete;
	CColliderManager& operator=(CColliderManager&&) = delete;

public:
	static CColliderManager& GetInstance();

	//�R���W�����R���|�[�l���g�̃|�C���^��ǉ�
	void AddCollider(CColliderComponent& collider);

	//�����ȊO�̃R���W�����R���|�[�l���g�̃|�C���^��������
	bool GetColliders(CColliderComponent* caller, std::vector<CColliderComponent*>& result);

	//�o�^���Ă���R���W�����f�[�^�̉��
	void ReleaseCollider(CColliderComponent& collider);

	void Update();
};