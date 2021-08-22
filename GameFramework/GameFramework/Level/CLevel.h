#pragma once
#include <vector>
#include <memory>
#include <functional>

#include "../Object/CObject.h"
#include "../Actor/CActor.h"
#include "../Interfaces/IRender.h"

class IGame;
class IRender;
class CGame;
class CLevel;
class CGameManager;
class IGameManagerToLevel;
class CCameraComponent;

class ILevel
{
public:
	virtual ~ILevel() {};
	virtual void DestroyActor(CActor& target) = 0;
	virtual void AddActor(CActor& actor) = 0;
	virtual void RequestSetCamera(CCameraComponent& camera) = 0;
	virtual void AddImGuiDrawMethod(std::function<void()> method) = 0;
	virtual void AddAlphaRenderComponent(IRender& renderTarget, bool isFront) = 0;
	virtual void Add2DRenderComponent(IRender& renderTarget) = 0;
	virtual void RequestLoadLevel(CLevel& level) = 0;
};

//���x���N���X
class CLevel :public CObject, public ILevel
{
private:
	std::vector<std::unique_ptr<CActor>> mActors;					//�A�N�^�[
	std::vector<std::function<void()>> mDoAfterTickFunction;		//Tick��ɍs���֐��I�u�W�F�N�g
	std::vector<std::function<void()>> mImGuiDrawMethod;			//ImGui�ɍs�킹��`��̊֐��I�u�W�F�N�g
	std::vector<IRender*> mAlphaRenderComponents;
	std::vector<IRender*> m2DRenderComponents;

	CCameraComponent* mRenderingCamera = nullptr;		//�����_�[��S������J����

protected:
	IGame* mOwnerInterface;			//�Q�[���C���^�[�t�F�[�X

private:
	//�R�s�[�֎~
	CLevel(const CLevel&) = delete;
	CLevel& operator=(const CLevel&) = delete;

	/*�A�N�^�[�ǉ�
	�����d�v��
	�q�N���X�͌ĂԂ��Ƃ͂ł��Ȃ�
	�A�N�^�[�̃R���X�g���N�^���ĂԂ��ƂŃA�N�^�[�̎Q�Ƃ���H���Ă��̃��\�b�h���Ă΂��
	*/
	void AddActor(CActor& actor)override;

	//�A�N�^�[�̔j��
	void DestroyActor(CActor& target)override;

	void AddAlphaRenderComponent(IRender& renderTarget, bool isFront)override
	{
		if (isFront)
		{
			auto itr = mAlphaRenderComponents.begin();
			mAlphaRenderComponents.emplace(itr, &renderTarget);
		}
		else mAlphaRenderComponents.emplace_back(&renderTarget);
	}

	void Add2DRenderComponent(IRender& renderTarget)override
	{
		m2DRenderComponents.emplace_back(&renderTarget);
	}

	void RequestLoadLevel(CLevel& level)override;

protected:
	//�J�����̃Z�b�g�����N�G�X�g
	void RequestSetCamera(CCameraComponent& camera)override;

	void AddImGuiDrawMethod(std::function<void()> method)override
	{
		mImGuiDrawMethod.emplace_back(method);
	}

	template<class T>
	bool GetActor(CActor*& result)
	{
		for (auto& actor : mActors)
		{
			if (typeid(T) == typeid(*actor))
			{
				result = actor.get();
				return true;
			}
		}
		return false;
	}

	template<class T>
	bool GetAllActor(std::vector<CActor*>& result)
	{
		for (auto& actor : mActors)
		{
			if (typeid(T) == typeid(*actor))
			{
				result.emplace_back(actor.get());
			}
		}
		if (result.size() != 0)return true;
		else return false;
	}

public:
	//�����d�v���@�R���X�g���N�^���ĂԂ��Ƃ̓��x���̑J�ڂ��Ӗ�����
	CLevel(IGame& owner);

	/*
	�����d�v��
	�Q�[���}�l�[�W���[�Ƀ��x���𑗂�ꍇ�̂݃Q�[���̎Q�ƂȂ��ŃR���X�g���N�^���Ăяo���\
	�J�n���x���̐ݒ�̂��߂Ȃ̂ň�x�̂݉\��x�ڂ���̓G���[�ŏI������
	*/
	CLevel(IGameManagerToLevel& receiver);

	virtual ~CLevel() {};

	//������
	virtual void Init() = 0;

	//�X�V
	void Update()override;

	/*
	���t���[���s�������i�q�N���X�̂��߂̋@�\�j
	�v���g�^�C�v�Ȃǂ̊ȒP�Ɏ����������̂��߂ɗp�ӂ����̂�
	�{����ł̗��p�͔񐄏�
	�|�[�Y�Ȃǂ̐��䂪����Ă��Ȃ��̂Ńo�O�̉����ɂȂ�
	*/
	virtual void Tick() {};

	//�`��
	void Render()override;

	//�C���^�[�t�F�[�X�̃Z�b�g�@�Q�[���}�l�[�W���[���炵���Ăяo���z������Ă��Ȃ�
	void SetOwnerInterface(CGame& owner);

	const XMFLOAT4X4* GetRenderingCameraViewMatrix()const;

};