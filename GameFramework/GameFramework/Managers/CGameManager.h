//!
//! @file
//! @brief �Q�[���}�l�[�W���[�̃w�b�_�[�t�@�C��
//!

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

//! @brief �Q�[���}�l�[�W���[�N���X
class CGameManager
{
private:
	CGame mGame;								//!< �Q�[���N���X
	IGameToGameManager* mGameInterface;			//!< �Q�[���Ƃ̃C���^�[�t�F�[�X

	float mDeltaTime;							//!< �f���^�^�C��(1�b�P��)

	bool mCanExecute = true;					//!< ���s�ł��邩
	bool mCanSetStartLevel = true;				//!< �X�^�[�g���x�����Z�b�g�ł��邩
	bool mIsPause = false;						//!< �|�[�Y���Ă��邩

	//! @brief �R���X�g���N�^
	CGameManager();

	//�R�s�[�����[�u�֎~
	CGameManager(const CGameManager&) = delete;
	CGameManager& operator=(const CGameManager&) = delete;
	CGameManager(CGameManager&&) = delete;
	CGameManager& operator=(CGameManager&&) = delete;

public:
	//!
	//! @brief �C���X�^���X�擾
	//! @return CGameManager& �C���X�^���X
	//!
	static CGameManager& GetInstance();

	//!
	//! @brief ���s�����N�G�X�g
	//! @param[in] hInst �C���X�^���X�n���h��
	//! @param[in] winMode �E�B���h�E���[�h
	//!
	void RequestExecute(HINSTANCE hInst , int winMode);

	//!
	//! @brief �`��S���J�����̃r���[�s��擾
	//! @return const XMFLOAT4X4* �`��S���J�����̃r���[�s��i�`��S���J������������Ȃ��ꍇ��nullptr�j
	//!
	const XMFLOAT4X4* GetCameraViewMatrix();

	//!
	//! @brief �`��S���J�����̃��P�[�V�����擾
	//! @return XMFLOAT3 �`��S���J�����̃��P�[�V�����i�`��S���J������������Ȃ��ꍇ�͑S��0.0f�j
	//!
	XMFLOAT3 GetCameraLocation();

	//!
	//! @brief �����̃��P�[�V�����ƕ`��S���J�����Ƃ̋������Z�o
	//! @param[in] compareLocation �`��S���J�����Ƃ̋������r���郍�P�[�V����
	//! @return float ���ʂ̋����i�`��S���J������������Ȃ��ꍇ�͔�r���郍�P�[�V�������x�N�g���Ƃ��������ƂȂ�j
	//!
	float CalcDistanceToCamera(const XMFLOAT3& compareLocation);

	//!
	//! @brief �Q�[���C���^�[�t�F�[�X�擾
	//! @details �Q�[���V�X�e�����Q�[���C���^�[�t�F�[�X�ɃA�b�v�L���X�g��ԁi�@�\�𐧌�������ԁj�ŕԂ�
	//! @return IGame& �Q�[���C���^�[�t�F�[�X
	//!
	IGame& GetGameInterface()
	{
		return mGame;
	}

	//!
	//! @brief ���x���C���^�[�t�F�[�X�擾
	//! @details ���x�������x���C���^�[�t�F�[�X�ɃA�b�v�L���X�g��ԁi�@�\�𐧌�������ԁj�ŕԂ�
	//! @return IGame& ���x���C���^�[�t�F�[�X
	//!
	ILevel& GetLevelInterface()
	{
		return mGame.GetLevel();
	}

	//!
	//! @brief �E�B���h�E�n���h���擾
	//! @details ImGui�p�̑[�u�Ȃ̂Ŏg�p�͔񐄏�
	//! @return HWND �E�B���h�E�n���h��
	//!
	HWND GetHWnd()
	{
		return static_cast<IGameToGameManager&>(mGame).GetApp().GetHWnd();
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

	void SetDeltaTime(int64_t dt)
	{
		//�b�P�ʂɕϊ�
		mDeltaTime = dt / 1000.0f;
	}

};