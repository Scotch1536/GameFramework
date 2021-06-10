#pragma once
#include <memory>

#include "CGame.h"

class CLevel;
class CGame;
class IGame;
class Application;

class IGameManagerToLevel
{
public:
	virtual ~IGameManagerToLevel() {};
	virtual void SetStartLevel(CLevel& startLevel) = 0;
};

//�Q�[���}�l�[�W���[�N���X�F�V���O���g��
class CGameManager :public IGameManagerToLevel
{
private:
	std::unique_ptr<CGame> mGame;			//�Q�[���N���X

	bool mCanExecute = true;				//���s�ł��邩
	bool mCanSetStartLevel = true;			//�X�^�[�g���x�����Z�b�g�ł��邩

	CGameManager();

	//�R�s�[�����[�u�֎~
	CGameManager(const CGameManager&) = delete;
	CGameManager& operator=(const CGameManager&) = delete;
	CGameManager(CGameManager&&) = delete;
	CGameManager& operator=(CGameManager&&) = delete;

	//�X�^�[�g���x���̃Z�b�g
	void SetStartLevel(CLevel& startLevel)override;
public:
	static CGameManager& GetInstance();

	//���s�����N�G�X�g
	void RequestExecute(HINSTANCE hInst , int winMode);

	//�Q�[���N���X�̎擾�i�A�v���P�[�V�����N���X�̎Q�Ƃ��K�v�j
	CGame& GetGame(Application& partner);

	IGame& GetGameInterface()
	{
		return *mGame;
	}
};