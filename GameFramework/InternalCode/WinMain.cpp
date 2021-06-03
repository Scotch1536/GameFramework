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
#pragma comment (lib,"directxtex.lib")				// �����N�Ώۃ��C�u����
#pragma comment (lib,"dxguid.lib")					// �����N�Ώۃ��C�u����
#pragma comment (lib,"dinput8.lib")					// �����N�Ώۃ��C�u����
#pragma comment (lib,"assimp-vc141-mtd.lib")		// �����N�Ώۃ��C�u����

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include <Windows.h>
#include "CGame.h"

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
INT APIENTRY WinMain(HINSTANCE  h_hInst,
					 HINSTANCE  h_hPrevInst,
					 LPSTR		h_lpszArgs,
					 int		h_nWinMode)
{
	CGame& game = CGame::GetInstance();

	game.Execute(h_hInst , h_nWinMode);
}


//******************************************************************************
//	End of file.
//******************************************************************************

	