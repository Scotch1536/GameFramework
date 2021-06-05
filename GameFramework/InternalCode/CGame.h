#pragma once
#include <Windows.h>
#include <memory>

#include "CGameManager.h"
#include "CLevel.h"

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
	friend CGameManager;

	static bool mCanInstance;	//�C���X�^���X���ł��邩

	std::unique_ptr<CLevel> mLevel;		//���x��

	CGame();

	//�R�s�[�����[�u�֎~
	CGame(const CGame&) = delete;
	CGame& operator=(const CGame&) = delete;
	CGame(CGame&&) = delete;
	CGame& operator=(CGame&&) = delete;

	//���s�@�����̃��\�b�h���G���g���[�|�C���g�̊֐��ŌĂׂ΃E�B���h�E������Q�[�����X�^�[�g����
	long Execute(HINSTANCE hInst , int winMode)const;

public:
	//���x���̃��[�h�i�J�ځj
	void LoadLevel(CLevel& level)override;

	//�Q�[���̏������i�E�B���h�E�쐬��ɌĂяo���j
	void Init();

	void Input(uint64_t deltatime);
	void Update(uint64_t deltatime);
	void Render(uint64_t deltatime);
};

