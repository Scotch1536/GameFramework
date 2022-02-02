//!
//!	@file
//!	@brief �Q�[���V�X�e���̃w�b�_�[�t�@�C��
//!

#pragma once
#include <Windows.h>
#include <memory>
#include <functional>

#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/Memory.h"
#include "../Level/CLevel.h"
#include "CApplication.h"

class CLevel;
class CGameManager;
class CApplication;

//! @brief ��ʗp�Q�[���C���^�[�t�F�[�X�N���X
class IGame
{
public:
	//! @brief �f�X�g���N�^
	virtual ~IGame() {};

	//!
	//! @brief ���x���̃��[�h�i�J�ځj
	//! @param[in] level ���[�h���郌�x��
	//! @param[in] isFeed �t�F�[�h���邩(�t�F�[�h�A�E�g)
	//! @param[in] feedColor �t�F�[�h���̐F���
	//! @param[in] feedTime �t�F�[�h�ɂ�����b��
	//!
	virtual void LoadLevel(CLevel& level , bool isFeed = false , XMFLOAT3 feedColor = { 1.0f,1.0f,1.0f } , float feedTime = 1.0f) = 0;
};

//! @brief �Q�[���}�l�[�W���[�p�Q�[���C���^�[�t�F�[�X�N���X
class IGameToGameManager
{
public:
	//! @brief �f�X�g���N�^
	virtual ~IGameToGameManager() {};

	//!
	//! @brief ���s
	//! @param[in] hInst �C���X�^���X�n���h��
	//! @param[in] winMode �E�B���h�E���[�h
	//! @return unsigned long  �E�B���h�E���b�Z�[�W
	//!
	virtual unsigned long Execute(HINSTANCE hInst , int winMode) = 0;

	//!
	//! @brief ���x���̃Z�b�g
	//! @param[in] level �Z�b�g���郌�x��
	//!
	virtual void SetLevel(CLevel& level) = 0;

	//!
	//! @brief �A�v���P�[�V�����̎擾
	//! @return CApplication �A�v���P�[�V�����V�X�e��
	//!
	virtual CApplication& GetApp() = 0;
};

//! @brief �Q�[���V�X�e���N���X
class CGame final :public IGame , public IGameToGameManager
{
private:
	//! @brief �r���[�|�[�g�萔�o�b�t�@�\����
	ALIGN16 struct SConstantBufferViewPort
	{
		uint32_t ScreenWidth;		//!< �X�N���[������
		uint32_t ScreenHeight;		//!< �X�N���[���c��
	};

	ComPtr<ID3D11Buffer> mConstantBufferViewPort = nullptr;			//!< �r���[�|�[�g�萔�o�b�t�@

	CApplication mApp;												//!< �A�v���P�[�V����

	std::unique_ptr<CLevel> mLevel;									//!< ���x��

	std::function<void()> mLoadLevelEvent;							//!< ���[�h���x���C�x���g

	//�R�s�[�����[�u�֎~
	CGame(const CGame&) = delete;
	CGame& operator=(const CGame&) = delete;
	CGame(CGame&&) = delete;
	CGame& operator=(CGame&&) = delete;

	//!
	//! @brief ���s
	//! @param[in] hInst �C���X�^���X�n���h��
	//! @param[in] winMode �E�B���h�E���[�h
	//! @return unsigned long  �E�B���h�E���b�Z�[�W
	//!
	unsigned long Execute(HINSTANCE hInst , int winMode)override;

	//!
	//! @brief ���x���̃Z�b�g
	//! @param[in] level �Z�b�g���郌�x��
	//!
	void SetLevel(CLevel& level)override;

	//!
	//! @brief ���x���̃��[�h�i�J�ځj
	//! @param[in] level ���[�h���郌�x��
	//! @param[in] isFeed �t�F�[�h���邩(�t�F�[�h�A�E�g)
	//! @param[in] feedColor �t�F�[�h���̐F���
	//! @param[in] feedTime �t�F�[�h�ɂ�����b��
	//!
	void LoadLevel(CLevel& level , bool isFeed = false , XMFLOAT3 feedColor = { 1.0f,1.0f,1.0f } , float feedTime = 1.0f)override;

	//!
	//! @brief �A�v���P�[�V�����̎擾
	//! @return CApplication �A�v���P�[�V�����V�X�e��
	//!
	CApplication& GetApp()override
	{
		return mApp;
	}

public:
	//! 
	//! @brief �R���X�g���N�^
	//! @param[in] partner ���̃Q�[���V�X�e�������L����Q�[���}�l�[�W���[
	//!
	CGame(CGameManager& partner);

	//! @brief �f�X�g���N�^
	~CGame();

	//! @brief �������i�E�B���h�E�쐬��ɌĂяo���j
	void Init();

	//! @brief ����
	void Input();

	//! @brief �X�V
	void Update();

	//! @brief �`��
	void Render();

	CLevel& GetLevel()
	{
		return *mLevel;
	}

};

