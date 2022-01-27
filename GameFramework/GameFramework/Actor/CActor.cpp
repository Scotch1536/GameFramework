//!
//! @file
//! @brief �A�N�^�[�֘A�̃\�[�X�t�@�C��
//!

#include "../Level/CLevel.h"
#include "../Interfaces/IRender.h"
#include "../Managers/CInputManager.h"

#include "CActor.h"

CActor::CActor(ILevel& owner, bool isAffectToPause)
	:CObject("Actor"),
	mOwnerInterface(owner), mIsAffectToPause(isAffectToPause),
	Transform(*this)
{
	//�A�N�^�[�ǉ�
	mOwnerInterface.AddActor(*this);
}

CActor::~CActor()
{
	//���̓}�l�[�W���[�Ǝ��g�̃o�C���h��؂藣��
	CInputManager::GetInstance().ReleaseBindTarget(*this);
}

void CActor::AddComponent(CComponent& component)
{
	int myPriority = component.GetPriority();
	auto itr = this->mComponents.begin();

	for (; itr != this->mComponents.end(); ++itr)
	{
		//�����Ɠ����|�C���^�����������ꍇ�I��
		if ((*itr).get() == &component)return;

		//���g�̗D��x�̕����Ⴂ�ꍇ
		if (myPriority <= (*itr)->GetPriority())
		{
			break;
		}
	}
	//�R���|�[�l���g��}��
	this->mComponents.emplace(itr, &component);
}

void CActor::AddRenderOrder(const SRenderInfo& order)
{
	//�`�施�ߒǉ�
	mRenderOrders.emplace_back(order);
}

void CActor::RequestAddDoBeforeUpdateFunction(std::function<void()> func)
{
	//���x���̍X�V�O���s�֐��ɒǉ�
	mOwnerInterface.AddDoBeforeUpdateFunction(func);
}

void CActor::Update()
{
	//�g�����X�t�H�[���X�V
	Transform.Update();

	for(auto& component : mComponents)
	{
		//�R���|�[�l���g�X�V
		component->Update();
	}
}

void CActor::Render()
{
	//�`�施�߂̃��N�G�X�g
	mOwnerInterface.RequestRenderOrders(mRenderOrders);
}

void CActor::Destroy()
{
	//�A�N�^�[�̔j��
	mOwnerInterface.DestroyActor(*this);
}