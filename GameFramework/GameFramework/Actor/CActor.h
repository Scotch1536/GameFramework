#pragma once
#include <vector>
#include <memory>
#include <string>

#include "../Object/CObject.h"
#include "../Components/CComponent.h"
#include "../Transform/CTransform.h"
#include "../Interfaces/IRender.h"

class ILevel;
class CTransform;

//�C���^�[�t�F�[�X
class IActor
{
public:
	virtual CActor& GetActor() = 0;
	virtual ~IActor() {};
};

class IActorToComponent :public IActor
{
public:
	virtual ~IActorToComponent() {};
	virtual void AddComponent(CComponent& component) = 0;
	virtual void AddRenderComponent(IRender& component) = 0;
	virtual CTransform& GetTransform() = 0;
	virtual void RequestAddAlphaRenderComponentToLevel(IRender& renderTarget , bool isFront = false) = 0;
	virtual void RequestAdd2DRenderComponentToLevel(IRender& renderTarget) = 0;
};

//�A�N�^�[�N���X
class CActor :public CObject , public IActorToComponent
{
private:
	std::vector<std::unique_ptr<CComponent>> mComponents;		//�R���|�[�l���g
	std::vector<IRender*> mRenderComponents;					//�`��̑��������R���|�[�l���g
	std::vector<std::string> mActorTags;						//�^�O

	//�R�s�[�֎~
	//CActor(const CActor&) = delete;
	//CActor& operator=(const CActor&) = delete;

	/*�R���|�[�l���g�ǉ�
	�����d�v���q�N���X�͌ĂԂ��Ƃ͂ł��Ȃ�
	�R���|�[�l���g�̃R���X�g���N�^���ĂԂ��ƂŃA�N�^�[�̎Q�Ƃ���H���Ă��̃��\�b�h���Ă΂��
	*/
	void AddComponent(CComponent& component)override;

	//�����_�[�@�\�����R���|�[�l���g��o�^
	void AddRenderComponent(IRender& component)override;

	void RequestAddAlphaRenderComponentToLevel(IRender& renderTarget , bool isFront)override;

	void RequestAdd2DRenderComponentToLevel(IRender& renderTarget)override;


	//�A�N�^�[���擾
	CActor& GetActor()override
	{
		return *this;
	}

	//�g�����X�t�H�[���擾
	CTransform& GetTransform()override
	{
		return Transform;
	}

protected:
	ILevel& mOwnerInterface;		//�C���^�[�t�F�[�X

	bool mIsAffectToPause;			//�|�[�Y�̉e�����󂯂邩�ǂ���

public:
	CTransform Transform;			//�g�����X�t�H�[��

	//�����d�v���@�A�N�^�[�̃R���X�g���N�^���ĂԂ��Ƃ̓��x���ɃA�N�^�[��ǉ����邱�Ƃ��Ӗ�����
	CActor(ILevel& owner , bool isAffectToPause = true);

	virtual ~CActor();

	/*�X�V
	�����d�v�����̃��\�b�h���I�[�o�[���C�h����ꍇ�͕K���Ō�ɐe�̃��\�b�h���ĂԂ���
	*/
	void Update()override;

	//���t���[���s�������i�q�N���X�̂��߂̋@�\�j
	virtual void Tick() {};

	//�`��
	void Render()override;

	//�j��
	void Destroy();

	//�ՓˊJ�n���̃C�x���g
	virtual void EventAtBeginCollide(CActor& collideActor) {};

	//�ՓˏI�����̃C�x���g
	virtual void EventAtEndCollide(CActor& collideActor) {};

	void AddTag(std::string tag)
	{
		mActorTags.emplace_back(tag);
	}

	bool HasTag(std::string tag)
	{
		for(auto& actorTag : mActorTags)
		{
			if(actorTag == tag)return true;
		}
		return false;
	}

	template<class T>
	bool GetComponent(CComponent*& result)
	{
		for(auto& component : mComponents)
		{
			if(typeid(T) == typeid(*component))
			{
				result = component.get();
				return true;
			}
		}
		return false;
	}

	template<class T>
	bool GetAllComponents(std::vector<CComponent*>& result)
	{
		for(auto& component : mComponents)
		{
			if(typeid(T) == typeid(*component))
			{
				result.emplace_back(component.get());
			}
		}
		if(result.size() != 0)return true;
		else return false;
	}

	void SetIsAffectToPause(bool flg)
	{
		mIsAffectToPause = flg;
	}

	const bool& GetIsAffectToPause()const
	{
		return mIsAffectToPause;
	}
};