#pragma once
#include "../Game/CGame.h"

class CLevel;
class CGame;
class IGame;
class CApplication;

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
	CGame mGame;			//�Q�[���N���X

	int64_t mDeltaTime;		//�f���^�^�C��

	bool mCanExecute = true;				//���s�ł��邩
	bool mCanSetStartLevel = true;			//�X�^�[�g���x�����Z�b�g�ł��邩
	bool mIsPause = false;

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
	CGame& GetGame(const CApplication& partner)
	{
		return mGame;
	}

	const IGame& GetGameInterface()const
	{
		return mGame;
	}

	const bool& GetIsPause()const
	{
		return mIsPause;
	}

	const int64_t& GetDeltaTime()const
	{
		return mDeltaTime;
	}

	void SetIsPause(bool flg)
	{
		mIsPause = flg;
	}

	void SetDeltaTime(const CApplication& partner , int64_t dt)
	{
		mDeltaTime = dt;
	}

	HWND GetHWnd()
	{
		return static_cast<IGameToGameManager&>(mGame).GetApp().GetHWnd();
	}
};