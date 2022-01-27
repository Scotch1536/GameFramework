#pragma once
#pragma comment (lib,"d3d11.lib")					// �����N�Ώۃ��C�u����
#pragma comment (lib,"dxgi.lib")					// �����N�Ώۃ��C�u����
#pragma comment (lib,"D3DCompiler.lib")				// �����N�Ώۃ��C�u����
#pragma comment (lib,"winmm.lib")					// �����N�Ώۃ��C�u����
#pragma comment (lib,"dxguid.lib")					// �����N�Ώۃ��C�u����
#pragma comment (lib,"dinput8.lib")					// �����N�Ώۃ��C�u����

#pragma comment (lib,"assimp-vc141-mtd.lib")		// �����N�Ώۃ��C�u����

#ifdef _DEBUG
#pragma comment (lib,"_debug/directxtex.lib")		// �����N�Ώۃ��C�u����
#else
#pragma comment (lib,"_release/directxtex.lib")		// �����N�Ώۃ��C�u����
#endif

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

	//�J�����̃r���[�s��i�|�C���^�j���擾�i�J�������Ȃ��ꍇnullptr)
	const XMFLOAT4X4* GetCameraViewMatrix();

	//�g�p���̃J�����̈ʒu���擾
	XMFLOAT3 GetCameraLocation();

	//�g�p���̃J�����Ƃ̋������Z�o�i�J�������Ȃ��ꍇ0.0f�j
	float CalcDistanceToCamera(const XMFLOAT3& compareLocation);

	//�Q�[���N���X�̎擾�i�A�v���P�[�V�����N���X�̎Q�Ƃ��K�v�j
	CGame& GetGame(const CApplication& partner)
	{
		return mGame;
	}

	IGame& GetGameInterface()
	{
		return mGame;
	}

	ILevel& GetLevelInterface()
	{
		return mGame.GetLevel();
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