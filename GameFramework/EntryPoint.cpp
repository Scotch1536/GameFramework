//!
//!	@file
//!	@brief �G���g���[�|�C���g
//!	@note �A�v���P�[�V�����J�n
//!

#include <Windows.h>
#include "GameFramework/Managers/CGameManager.h"

#include "CTitle.h"

INT APIENTRY WinMain(HINSTANCE  h_hInst ,
	HINSTANCE  h_hPrevInst ,
	LPSTR		h_lpszArgs ,
	int		h_nWinMode)
{
	//�Q�[���}�l�[�W���[�擾
	CGameManager& gameManager = CGameManager::GetInstance();

	/*
	�����d�v��
	�����ɊJ�n���������x���̃R���X�g���N�^��
	������IGame&�ŌĂяo��
	����������̓Q�[���}�l�[�W���[���s���̂ōl���Ȃ��Ă悢
	*/
	new CTitle(gameManager.GetGameInterface());

	//�Q�[���̎��s�����N�G�X�g
	gameManager.RequestExecute(h_hInst , h_nWinMode);
}