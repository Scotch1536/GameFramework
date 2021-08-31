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
	virtual void AddImGuiDrawFunction(std::function<void()> func) = 0;
	virtual void RequestRenderOrders(std::vector<SRenderInfo>& renderOrders) = 0;
	virtual void AddDoBeforeUpdateFunction(std::function<void()> func) = 0;
};

//���x���N���X
class CLevel :public CObject , public ILevel
{
private:
	std::vector<std::unique_ptr<CActor>> mActors;					//�A�N�^�[

	std::vector<std::function<void()>> mDoBeforeUpdateFunction;		//�X�V��ɍs���֐��I�u�W�F�N�g
	std::vector<std::function<void()>> mImGuiDrawFunction;			//ImGui�ɍs�킹��`��̊֐��I�u�W�F�N�g

	//�����_�[�R���|�[�l���g
	std::vector<IRender*> m3DOpacityRenderComponents;
	std::vector<IRender*> m3DTranslucentRenderComponents;
	std::vector<IRender*> m2DOpacityRenderComponents;
	std::vector<IRender*> m2DTranslucentRenderComponents;

	CCameraComponent* mRenderingCamera = nullptr;		//�����_�[��S������J����

protected:
	IGame& mOwnerInterface;			//�Q�[���C���^�[�t�F�[�X

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

	void Add3DOpacityRenderComponent(IRender& renderTarget)
	{
		m3DOpacityRenderComponents.emplace_back(&renderTarget);
	}

	void Add3DTranslucentRenderComponent(IRender& renderTarget , bool isFront = false)
	{
		if(isFront)
		{
			auto itr = m3DTranslucentRenderComponents.begin();
			m3DTranslucentRenderComponents.emplace(itr , &renderTarget);
		}
		else m3DTranslucentRenderComponents.emplace_back(&renderTarget);
	}

	void Add2DOpacityRenderComponent(IRender& renderTarget)
	{
		m2DOpacityRenderComponents.emplace_back(&renderTarget);
	}

	void Add2DTranslucentRenderComponent(IRender& renderTarget)
	{
		m2DTranslucentRenderComponents.emplace_back(&renderTarget);
	}

	void AddDoBeforeUpdateFunction(std::function<void()> func)override
	{
		mDoBeforeUpdateFunction.emplace_back(func);
	}

	void RequestRenderOrders(std::vector<SRenderInfo>& renderOrders)override;

protected:
	//�J�����̃Z�b�g�����N�G�X�g
	void RequestSetCamera(CCameraComponent& camera)override;

	void AddImGuiDrawFunction(std::function<void()> func)override
	{
		mImGuiDrawFunction.emplace_back(func);
	}

	template<class T>
	bool GetActor(CActor*& result)
	{
		for(auto& actor : mActors)
		{
			if(typeid(T) == typeid(*actor))
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
		for(auto& actor : mActors)
		{
			if(typeid(T) == typeid(*actor))
			{
				result.emplace_back(actor.get());
			}
		}
		if(result.size() != 0)return true;
		else return false;
	}

public:
	//�����d�v���@�R���X�g���N�^���ĂԂ��Ƃ̓��x���̑J�ڂ��Ӗ�����
	CLevel(IGame& owner , bool isFeed = false , XMFLOAT3 feedColor = { 1.0f,1.0f,1.0f } , float oneFrameAlpha = 0.01f);

	virtual ~CLevel();

	/*
	�����d�v��
	�A�N�^�[�̒ǉ��͊�{�����ōs��
	�R���|�[�l���g�ǉ����邱�Ƃ��ł��邪�񐄏�
	�R���|�[�l���g�̓A�N�^�[�̃R���X�g���N�^�Œǉ����邱�Ƃ𐄏�
	*/
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

	const XMFLOAT4X4* GetRenderingCameraViewMatrix()const;

};