//*****************************************************************************
//!	@file	WinMain.cpp
//!	@brief	
//!	@note	�A�v���P�[�V�����J�n
//!	@author	
//*****************************************************************************

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

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include <Windows.h>
#include "Managers/CGameManager.h"

#include "../CTestLevel.h"

//==============================================================================
//!	@fn		WinMain
//!	@brief	�G���g���|�C���g
//!	@param	�C���X�^���X�n���h��
//!	@param	�Ӗ��Ȃ�
//!	@param	�N�����̈���������
//!	@param	�E�C���h�E�\�����[�h
//!	@retval	TRUE�@�����I��/FALSE�@���s�I��
//!	@note	
//==============================================================================
INT APIENTRY WinMain(HINSTANCE  h_hInst ,
	HINSTANCE  h_hPrevInst ,
	LPSTR		h_lpszArgs ,
	int		h_nWinMode)
{
	//�Q�[���}�l�[�W���[�擾
	CGameManager& gameManager = CGameManager::GetInstance();

	/*�����d�v��
		�����ɊJ�n���������x���̃R���X�g���N�^��
		������CGameManager&�ŌĂяo��
		����������̓Q�[���}�l�[�W���[���s���̂ōl���Ȃ��Ă悢
		new StartLevelType(CGameManager&);
	*/
	*new CTestLevel(gameManager);

	//�Q�[���̎��s�����N�G�X�g
	gameManager.RequestExecute(h_hInst , h_nWinMode);
}

//******************************************************************************
//	End of file.
//******************************************************************************


