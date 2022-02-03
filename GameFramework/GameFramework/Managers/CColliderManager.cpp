//!
//! @file
//! @brief �R���C�_�[�}�l�[�W���[�̃\�[�X�t�@�C��
//!

#include "CColliderManager.h"
#include "../Components/CColliderComponent.h"

CColliderManager& CColliderManager::GetInstance()
{
	static CColliderManager instance;

	return instance;
};

void CColliderManager::AddCollider(CColliderComponent& collider)
{
	auto sameCollider = std::find(mColliders.begin() , mColliders.end() , &collider);

	//�����R���C�_�[������ΏI��
	if(sameCollider != mColliders.end())return;

	mColliders.emplace_back(&collider);

	//�L���b�V�����X�V���Ȃ���΂Ȃ�Ȃ����߃t���O�����ׂ�false�ɂ���
	for(auto& isCache : mIsCache)
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
	if(mIsCache.count(caller) == 0)
	{
		mIsCache[caller] = false;
	}

	//�O��̏�񂪂��������true�Ȃ�O��ƕύX�Ȃ�
	if(mIsCache[caller] == true)return true;

	std::string callerObjType = caller->GetObjectType();
	std::vector<CColliderComponent*> buf;
	for(auto& collider : mColliders)
	{
		//�Ăяo�����ƃ|�C���^����v���Ȃ����I�u�W�F�N�g�^�C�v��NONE���Ăяo�����ƈ�v���Ȃ��Ȃ��Ȃ��r�ΏۂƂ���
		if(collider != caller && collider->GetObjectType() == "NONE" || collider->GetObjectType() != callerObjType)
		{
			buf.push_back(collider);
		}
	}
	result = buf;

	mIsCache[caller] = true;		//�O��̏�񂪍ŐV�ɍX�V���ꂽ

	if(result.size() != 0)return true;		//�Ԃ��z�񂪂���ꍇ��true�Ԃ�
	else return false;						//�Ȃ��ꍇ��false��Ԃ�
}

void CColliderManager::ReleaseCollider(CColliderComponent& collider)
{
	//���݂��Ȃ��Ȃ�I��
	if(mIsCache.size() == 0)return;

	for(auto itr = mColliders.begin(); itr != mColliders.end(); itr++)
	{
		if((*itr) == &collider)
		{
			mColliders.erase(itr);
			mColliders.shrink_to_fit();
			break;
		}
	}

	if(mIsCache.count(&collider) != 0)mIsCache.erase(&collider);

	for(auto& isBefore : mIsCache)
	{
		isBefore.second = false;
	}
}

void CColliderManager::Update()
{
	if(mColliders.size() != 0)
	{
		for(auto& collider : mColliders)
		{
			//���[���h���W�n�̃R���C�_�[���ɕϊ�
			collider->ConvertWorldCollider();
		}
	}
}
