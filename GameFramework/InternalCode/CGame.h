#pragma once
#include <Windows.h>
#include <memory>

//���x����
enum class Level
{
	MAX_LEVELNUM ,
};

//�Q�[���N���X�i�V���O���g���j
class CGame
{
private:
	Level mLevel;
	//std::unique_ptr<CLevel> mLevelInfo;

	CGame();

	CGame(const CGame&) = delete;
	CGame& operator=(const CGame&) = delete;
	CGame(CGame&&) = delete;
	CGame& operator=(CGame&&) = delete;

	void LoadLevel();
public:
	static CGame& GetInstance();

	long Execute(HINSTANCE hInst , int winMode)const;

	void Init();	//�Q�[���̏������i�E�B���h�E�쐬��ɌĂяo���j

	void Input(uint64_t deltatime);
	void Update(uint64_t deltatime);
	void Render(uint64_t deltatime);
};

