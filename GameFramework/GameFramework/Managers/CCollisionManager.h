#pragma once
#include <vector>

class CCollisionComponent;

class CCollisionManager
{
private:
	std::vector<CCollisionComponent*> mColliders;

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
	bool GetColliders(const CCollisionComponent& caller, std::vector<CCollisionComponent*>& result);
};