#include "CColliderManager.h"
#include "../Components/CColliderComponent.h"

CColliderManager& CColliderManager::GetInstance()
{
	static CColliderManager instance;

	return instance;
};

void CColliderManager::AddCollider(CColliderComponent& collider)
{
	mColliders.emplace_back(&collider);

	for(auto& isCache : mIsBefore)
	{
		isCache.second = false;
	}
}

bool CColliderManager::GetColliders(CColliderComponent* caller , std::vector<CColliderComponent*>& result)
{
	//�Ăяo�������Ȃ���ΑS�ẴR���C�_�[��Ԃ�
	if(caller == nullptr)
	{
		result = mColliders;
		return true;
	}

	//�O��̏�񂪂Ȃ���΍��
	if(mIsBefore.count(caller) == 0)
	{
		mIsBefore[caller] = false;
	}

	//�O��̏�񂪂��������true�Ȃ�O��ƕύX�Ȃ�
	if(mIsBefore[caller] == true)return true;

	std::string callerObjType = caller->GetObjectType();
	std::vector<CColliderComponent*> buf;
	for(auto& collider : mColliders)
	{
		//�Ăяo�����ƃ|�C���^����v���Ȃ����I�u�W�F�N�g�^�C�v��NONE���Ăяo�����ƈ�v���Ȃ��Ȃ��Ȃ��r�ΏۂƂ���
		if(collider != caller && collider->GetObjectType() == "NONE"||collider->GetObjectType() != callerObjType)
		{
			buf.push_back(collider);
		}
	}
	result = buf;

	mIsBefore[caller] = true;		//�O��̏�񂪍ŐV�ɍX�V���ꂽ

	if(result.size() != 0)return true;		//�Ԃ��z�񂪂���ꍇ��true�Ԃ�
	else return false;						//�Ȃ��ꍇ��false��Ԃ�
}

void CColliderManager::ReleaseCollider(CColliderComponent& collider)
{
	for(auto itr = mColliders.begin(); itr != mColliders.end(); itr++)
	{
		if((*itr) == &collider)
		{
			mColliders.erase(itr);
			mColliders.shrink_to_fit();
			break;
		}
	}

	if(mIsBefore.size() != 0 && mIsBefore.count(&collider) != 0)mIsBefore.erase(&collider);

	if(mIsBefore.size() != 0)
	{
		for(auto& isBefore : mIsBefore)
		{
			isBefore.second = false;
		}
	}
}

void CColliderManager::Update()
{
	if(mColliders.size() != 0)
	{
		for(auto& collider : mColliders)
		{
			collider->ConvertWorldCollider();
		}
	}
}
