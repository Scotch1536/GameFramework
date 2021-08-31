#pragma once
#include "../Game/CGame.h"

class CLevel;
class CGame;
class IGame;
class CApplication;

//�Q�[���}�l�[�W���[�N���X�F�V���O���g��
class CGameManager
{
private:
	CGame mGame;			//�Q�[���N���X

	float mDeltaTime;		//�f���^�^�C��(1�b�P��)

	bool mCanExecute = true;				//���s�ł��邩
	bool mCanSetStartLevel = true;			//�X�^�[�g���x�����Z�b�g�ł��邩
	bool mIsPause = false;

	CGameManager();

	//�R�s�[�����[�u�֎~
	CGameManager(const CGameManager&) = delete;
	CGameManager& operator=(const CGameManager&) = delete;
	CGameManager(CGameManager&&) = delete;
	CGameManager& operator=(CGameManager&&) = delete;

public:
	static CGameManager& GetInstance();

	//���s�����N�G�X�g
	void RequestExecute(HINSTANCE hInst , int winMode);

	//�J�����̃r���[�s����擾
	const XMFLOAT4X4* GetCameraViewMatrix();

	//�Q�[���N���X�̎擾�i�A�v���P�[�V�����N���X�̎Q�Ƃ��K�v�j
	CGame& GetGame(const CApplication& partner)
	{
		return mGame;
	}

	IGame& GetGameInterface()
	{
		return mGame;
	}

	const bool& GetIsPause()const
	{
		return mIsPause;
	}

	const float& GetDeltaTime()const
	{
		return mDeltaTime;
	}

	void SetIsPause(bool flg)
	{
		mIsPause = flg;
	}

	void SetDeltaTime(const CApplication& partner , int64_t dt)
	{
		mDeltaTime = dt / 1000.0f;
	}

	HWND GetHWnd()
	{
		return static_cast<IGameToGameManager&>(mGame).GetApp().GetHWnd();
	}

};