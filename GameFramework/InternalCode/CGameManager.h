#pragma once
#include <memory>

class CGame;
class IGame;
class Application;

//�Q�[���}�l�[�W���[�N���X�@�i�V���O���g���j
class CGameManager
{
private:
	std::unique_ptr<CGame> mGame;		//�Q�[���N���X
	bool mCanExecute = true;			//���s�ł��邩

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

	//�Q�[���N���X�̎擾�i�A�v���P�[�V�����N���X�̎Q�Ƃ��K�v�j
	CGame& GetGame(Application& partner);

	IGame& GetGameInterface();
};