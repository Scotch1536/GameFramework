#pragma once
#include <vector>
#include <memory>

#include "CActor.h"
#include "IRender.h"

class IGame;
class CGame;
class CGameManager;
class IGameManagerToLevel;
class CCameraComponent;

class ILevel
{
public:
	virtual ~ILevel() {};
	virtual void DestroyActor(CActor& target) = 0;
};

class ILevelToActor
{
public:
	virtual ~ILevelToActor() {};
	virtual void AddActor(CActor& actor) = 0;
};

class CLevel :public ILevel , public ILevelToActor
{
private:
	std::vector<std::unique_ptr<CActor>> mActors;		//�A�N�^�[

	CCameraComponent* mRenderingCamera = nullptr;		//�����_�[��S������J����

	//�A�N�^�[�̔j��
	void DestroyActor(CActor& target)override;
protected:
	IGame* mOwnerInterface;			//�Q�[���C���^�[�t�F�[�X

private:
	//�R�s�[�֎~
	CLevel(const CLevel&) = delete;
	CLevel& operator=(const CLevel&) = delete;

	/*�A�N�^�[�ǉ�
	�����d�v���q�N���X�͌ĂԂ��Ƃ͂ł��Ȃ�
	�A�N�^�[�̃R���X�g���N�^���ĂԂ��ƂŃA�N�^�[�̎Q�Ƃ���H���Ă��̃��\�b�h���Ă΂��
	*/
	void AddActor(CActor& actor)override;
protected:
	//�J�����̃Z�b�g�����N�G�X�g
	void RequestSetCamera(CCameraComponent& camera);

public:
	//�����d�v���@�R���X�g���N�^���ĂԂ��Ƃ̓��x���̑J�ڂ��Ӗ�����
	CLevel(CGame& owner);

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
	void Update();

	//�`��
	void Render();

	//�C���^�[�t�F�[�X�̃Z�b�g�@�Q�[���}�l�[�W���[���炵���Ăяo���z������Ă��Ȃ�
	void SetOwnerInterface(CGame& owner);
};