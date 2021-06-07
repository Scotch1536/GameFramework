#pragma once
#include <Windows.h>
#include <memory>

//#include "CGameManager.h"
#include "CLevel.h"
#include "Application.h"

class CLevel;
class CGameManager;

//�C���^�[�t�F�[�X
class IGame
{
public:
	virtual ~IGame() {};
	virtual void LoadLevel(CLevel& level) = 0;
};

//�Q�[���N���X
class CGame :public IGame
{
private:
	//�t�����h�w��
	friend CGameManager;

	std::unique_ptr<Application> mApp;		//�A�v���P�[�V����
	std::unique_ptr<CLevel> mLevel;			//���x��

	CGame();

	//�R�s�[�����[�u�֎~
	CGame(const CGame&) = delete;
	CGame& operator=(const CGame&) = delete;
	CGame(CGame&&) = delete;
	CGame& operator=(CGame&&) = delete;

	//���s�@�����̃��\�b�h���G���g���[�|�C���g�̊֐��ŌĂׂ΃E�B���h�E������Q�[�����X�^�[�g����
	long Execute(HINSTANCE hInst , int winMode);

public:
	//���x���̃��[�h�i�J�ځj
	void LoadLevel(CLevel& level)override;

	//�Q�[���̏������i�E�B���h�E�쐬��ɌĂяo���j
	void Init();

	//����
	void Input(uint64_t deltatime);

	//�X�V
	void Update(uint64_t deltatime);

	//�`��
	void Render(uint64_t deltatime);
};

