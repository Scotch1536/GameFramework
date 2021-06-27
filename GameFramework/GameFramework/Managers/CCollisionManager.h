#pragma once
#include <vector>
#include <unordered_map>

class CCollisionComponent;

class CCollisionManager
{
private:
	std::vector<CCollisionComponent*> mColliders;
	std::unordered_map<CCollisionComponent* , bool> mIsBefore;

	CCollisionManager() = default;

	//�R�s�[�����[�u�֎~
	CCollisionManager(const CCollisionManager&) = delete;
	CCollisionManager& operator=(const CCollisionManager&) = delete;
	CCollisionManager(CCollisionManager&&) = delete;
	CCollisionManager& operator=(CCollisionManager&&) = delete;

public:
	static CCollisionManager& GetInstance();

	//�R���W�����R���|�[�l���g�̃|�C���^��ǉ�
	void AddCollider(CCollisionComponent& collider);

	//�����ȊO�̃R���W�����R���|�[�l���g�̃|�C���^��������
	bool GetColliders(CCollisionComponent* caller, std::vector<CCollisionComponent*>& result);

	//�o�^���Ă���R���W�����f�[�^�̍폜
	void ReleaseCollider(CCollisionComponent& collider);
};