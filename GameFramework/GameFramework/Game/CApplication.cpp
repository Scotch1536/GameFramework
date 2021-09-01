//*****************************************************************************
//!	@file	Application.cpp
//!	@brief	
//!	@note	�A�v���P�[�V�����N���X
//!	@author	
//*****************************************************************************

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include <Crtdbg.h>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <iostream>

#include "../ExternalCode/CWindow.h"
#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/CDirectxGraphics.h"
#include "../Game/CGame.h"
#include "../Managers/CGameManager.h"

#include "CApplication.h"

//-----------------------------------------------------------------------------
// �X�^�e�B�b�N�@�����o�[
//-----------------------------------------------------------------------------
const char*			CApplication::WINDOW_TITLE = "Attach!";
const char*			CApplication::WINDOW_CLASS_NAME = "win32app";

const uint32_t		CApplication::WINDOW_STYLE_WINDOWED = (WS_VISIBLE | WS_CAPTION | WS_SYSMENU);
const uint32_t		CApplication::WINDOW_EX_STYLE_WINDOWED = (0);
const uint32_t		CApplication::WINDOW_STYLE_FULL_SCREEN = (WS_VISIBLE | WS_POPUP);
const uint32_t		CApplication::WINDOW_EX_STYLE_FULL_SCREEN = (0);

const uint32_t		CApplication::CLIENT_WIDTH = 1280;
const uint32_t		CApplication::CLIENT_HEIGHT = 720;

uint32_t			CApplication::SYSTEM_WIDTH = 0;
uint32_t			CApplication::SYSTEM_HEIGHT = 0;

const float			CApplication::FPS = 60;

//==============================================================================
//!	@fn		CApplication
//!	@brief	�R���X�g���N�^
//!	@param	
//!	@retval	
//==============================================================================
CApplication::CApplication(CGame& partner): m_SystemCounter(0)
{}

//==============================================================================
//!	@fn		~Application
//!	@brief	�f�X�g���N�^
//!	@param	
//!	@retval	
//==============================================================================
CApplication :: ~CApplication()
{
	Dispose();
}


//==============================================================================
//!	@fn		InitSystemWH
//!	@brief	�V�X�e���̈�̕��ƍ�����������
//!	@param	
//!	@retval	
//==============================================================================
void CApplication::InitSystemWH()
{

}

//==============================================================================
//!	@fn		Init
//!	@brief	������
//!	@param	�C���X�^���X�n���h��
//!	@retval	
//==============================================================================
bool CApplication::Init(HINSTANCE h_Instance)
{
	// �������[���[�N�����o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#ifdef _DEBUG
	//// �R���\�[�������蓖�Ă�
	//AllocConsole();

	//// �W���o�͂̊��蓖��
	//freopen_s(&m_fp , "CON" , "w" , stdout);
#endif
	// ���ƍ���������
	InitSystemWH();

	// �E�C���h�E�쐬
	CWindow* window = CWindow::Instance();
	window->RegisterClass(h_Instance , WINDOW_CLASS_NAME , CS_OWNDC);

	window->SetWindow(h_Instance ,
		WINDOW_STYLE_WINDOWED ,
		WINDOW_EX_STYLE_WINDOWED ,
		NULL ,
		CLIENT_WIDTH + SYSTEM_WIDTH ,
		CLIENT_HEIGHT + SYSTEM_HEIGHT ,
		WINDOW_CLASS_NAME ,
		WINDOW_TITLE ,
		false);

	// HWND
	m_hWnd = window->GetHandle();

	//
	m_hInst = h_Instance;
	return true;
}

//==============================================================================
//!	@fn		Dispose
//!	@brief  �I������
//!	@param	
//!	@retval	
//==============================================================================
void CApplication::Dispose()
{
#ifdef _DEBUG
	//// �W���o�̓N���[�Y
	//fclose(m_fp);
	//// �R���\�[���J��
	//::FreeConsole();
#endif
	return;
}

//==============================================================================
//!	@fn		MainLoop
//!	@brief	���C�����[�v
//!	@param	
//!	@retval	���b�Z�[�WID
//==============================================================================
unsigned long CApplication::MainLoop()
{
	MSG		msg;
	ZeroMemory(&msg , sizeof(msg));

	CWindow* window = CWindow::Instance();

	uint64_t current_time = 0;
	uint64_t last_time = 0;

	CGame& game = CGameManager::GetInstance().GetGame(*this);

	// �^�C�}�𑜓x���~���b��
	::timeBeginPeriod(1);

	while(window->ExecMessage())
	{
		// timeGetTime�֐��́A�~���b�P�ʂŃV�X�e���������擾���܂��B 
		// �V�X�e�����Ԃ́AWindows���N�����Ă���̌o�ߎ��Ԃł��B
		current_time = ::timeGetTime();

		uint64_t delta_time = current_time - last_time;

		last_time = current_time;

		if(delta_time != current_time && delta_time < 1000)
		{
			CGameManager::GetInstance().SetDeltaTime(*this , delta_time);
		}

		//�Q�[���t���[
		game.Input();
		game.Update();
		game.Render();

		int64_t sleep_time = 16666 - delta_time;

		if(sleep_time > 0)
		{
			float tt = sleep_time / 1000.0f;
			//printf("sleep:%f \n", tt);
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(tt)));
			//�w�肵�����Ύ��Ԃ������X���b�h���u���b�N���� (function template)
		}
	}

	// �^�C�}�𑜓x�����ɖ߂�
	::timeEndPeriod(1);

	DX11SetTransform::GetInstance()->Uninit();

	// �������
	CDirectXGraphics::GetInstance()->Exit();

	return window->GetMessage();
}

//==============================================================================
//!	@fn		Input
//!	@brief	�L�[����
//!	@param	
//!	@retval	
//==============================================================================
void CApplication::Input(uint64_t deltatime)
{}

//==============================================================================
//!	@fn		Update
//!	@brief	�X�V
//!	@param	
//!	@retval	
//==============================================================================
void CApplication::Update(uint64_t deltatime)
{
	// �V�X�e���J�E���^
	m_SystemCounter++;
}

//==============================================================================
//!	@fn		Render
//!	@brief	�`��
//!	@param	
//!	@retval	
//==============================================================================
void CApplication::Render(uint64_t deltatime)
{}

//==============================================================================
//!	@fn		GetHWnd
//!	@brief	HWND �擾
//!	@param	
//!	@retval	HWND
//==============================================================================
HWND CApplication::GetHWnd()
{
	return m_hWnd;
}

//==============================================================================
//!	@fn		GetHInst
//!	@brief	HINSTANCE �擾
//!	@param	
//!	@retval	HINSTANCE
//==============================================================================
HINSTANCE CApplication::GetHInst()
{
	return m_hInst;
}

//******************************************************************************
//	End of file.
//******************************************************************************
