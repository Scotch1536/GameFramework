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

//�C���^�[�t�F�[�X
class IGame
{
public:
	virtual ~IGame() {};
	virtual void LoadLevel(CLevel& level , bool isFeed = false , XMFLOAT3 feedColor = { 1.0f,1.0f,1.0f } , float feedTime = 1.0f) = 0;
};

class IGameToGameManager
{
public:
	virtual ~IGameToGameManager() {};
	virtual void SetLevel(CLevel& level) = 0;
	virtual long Execute(HINSTANCE hInst , int winMode) = 0;
	virtual CApplication& GetApp() = 0;
};

//�Q�[���N���X
class CGame :public IGame , public IGameToGameManager
{
private:
	//�r���[�|�[�g�萔�o�b�t�@�\����
	ALIGN16 struct SConstantBufferViewPort
	{
		uint32_t ScreenWidth;
		uint32_t ScreenHeight;
	};

	ComPtr<ID3D11Buffer> mConstantBufferViewPort = nullptr;		//�r���[�|�[�g�萔�o�b�t�@

	CApplication mApp;		//�A�v���P�[�V����

	std::unique_ptr<CLevel> mLevel;			//���x��

	std::function<void()> mLoadLevelFunction;			//���[�h���x���̊֐����i�[���Ă����֐��I�u�W�F�N�g


	//�R�s�[�����[�u�֎~
	CGame(const CGame&) = delete;
	CGame& operator=(const CGame&) = delete;
	CGame(CGame&&) = delete;
	CGame& operator=(CGame&&) = delete;

	//�Q�[���t���[�̎��s
	long Execute(HINSTANCE hInst , int winMode)override;

	//���x���̃Z�b�g
	void SetLevel(CLevel& level)override;

	//���x���̃��[�h�i���x���̑J�ځA�ύX�j
	void LoadLevel(CLevel& level , bool isFeed = false , XMFLOAT3 feedColor = { 1.0f,1.0f,1.0f } , float feedTime = 1.0f)override;

	CApplication& GetApp()override
	{
		return mApp;
	}

public:
	CGame(CGameManager& partner);
	~CGame();

	//�Q�[���̏������i�E�B���h�E�쐬��ɌĂяo���j
	void Init();

	//����
	void Input();

	//�X�V
	void Update();

	//�`��
	void Render();

	const CLevel& GetLevel()
	{
		return *mLevel;
	}
};

