//!
//!	@file
//!	@brief �G���g���[�|�C���g�̃\�[�X�t�@�C��
//!

#include <Windows.h>
#include "GameFramework/Managers/CGameManager.h"

#include "CTitle.h"

//!
//! @brief �G���g���[�|�C���g
//! @param[in] hInst �C���X�^���X�n���h��
//! @param[in] hPrevInst ���ɂȂ�
//! @param[in] lpCmdLine �R�}���h���C��
//! @param[in] winMode �E�B���h�E���[�h
//! @return INT �I���R�[�h
//!
INT APIENTRY WinMain(HINSTANCE hInst , HINSTANCE  hPrevInst , LPSTR lpCmdLine , int winMode)
{
	//�Q�[���}�l�[�W���[�擾
	CGameManager& gameManager = CGameManager::GetInstance();

	//�������x���̍쐬
	new CTitle(gameManager.GetGameInterface());

	//�Q�[���̎��s�����N�G�X�g
	gameManager.RequestExecute(hInst , winMode);
}