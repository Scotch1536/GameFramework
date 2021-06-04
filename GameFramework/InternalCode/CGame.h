#pragma once
#include <Windows.h>
#include <memory>

#include "CLevel.h"

//�Q�[���N���X�i�V���O���g���j
class CGame
{
private:
	std::unique_ptr<CLevel> mLevel;

	CGame();

	CGame(const CGame&) = delete;
	CGame& operator=(const CGame&) = delete;
	CGame(CGame&&) = delete;
	CGame& operator=(CGame&&) = delete;

public:
	static CGame& GetInstance();

	//���s�@�����̃��\�b�h���G���g���[�|�C���g�̊֐��ŌĂׂ΃E�B���h�E������Q�[�����X�^�[�g����
	long Execute(HINSTANCE hInst , int winMode)const;

	void Init();	//�Q�[���̏������i�E�B���h�E�쐬��ɌĂяo���j

	void Input(uint64_t deltatime);
	void Update(uint64_t deltatime);
	void Render(uint64_t deltatime);

	//���x���̃��[�h�i�J�ځj
	void LoadLevel(CLevel& level);
};

