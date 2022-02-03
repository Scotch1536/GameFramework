//!
//!	@file
//!	@brief �A�v���P�[�V�����V�X�e���̃\�[�X�t�@�C��	
//!

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

//�X�^�e�B�b�N�����o������
const char* CApplication::WINDOW_TITLE = "Attach!";
const char*	CApplication::WINDOW_CLASS_NAME = "win32app";

const uint32_t CApplication::WINDOW_STYLE_WINDOWED = (WS_VISIBLE | WS_CAPTION | WS_SYSMENU);
const uint32_t CApplication::WINDOW_EX_STYLE_WINDOWED = (0);
const uint32_t CApplication::WINDOW_STYLE_FULL_SCREEN = (WS_VISIBLE | WS_POPUP);
const uint32_t CApplication::WINDOW_EX_STYLE_FULL_SCREEN = (0);

const uint32_t CApplication::CLIENT_WIDTH = 1280;
const uint32_t CApplication::CLIENT_HEIGHT = 720;

const float CApplication::FPS = 60;

void CApplication::Init(HINSTANCE hInstance)
{
	//�������[���[�N�����o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	//�E�C���h�E�쐬
	CWindow* window = CWindow::Instance();
	window->RegisterClass(hInstance , WINDOW_CLASS_NAME , CS_OWNDC);

	window->SetWindow(hInstance ,
		WINDOW_STYLE_WINDOWED ,
		WINDOW_EX_STYLE_WINDOWED ,
		NULL ,
		CLIENT_WIDTH ,
		CLIENT_HEIGHT ,
		WINDOW_CLASS_NAME ,
		WINDOW_TITLE ,
		false);

	mHWnd = window->GetHandle();
	mHInstance = hInstance;
}

unsigned long CApplication::MainLoop()
{
	MSG	msg;
	ZeroMemory(&msg , sizeof(msg));

	CWindow* window = CWindow::Instance();

	uint64_t current_time = 0;
	uint64_t last_time = 0;

	//�^�C�}�𑜓x���~���b��
	::timeBeginPeriod(1);

	while(window->ExecMessage())
	{
		//timeGetTime�֐��̓~���b�P�ʂŃV�X�e���������擾 
		//�V�X�e�����Ԃ�Windows���N�����Ă���̌o�ߎ���
		current_time = ::timeGetTime();

		//�f���^�^�C���Z�o
		uint64_t delta_time = current_time - last_time;

		last_time = current_time;

		//�f���^�^�C�����X�V���ꂽ��ŋK�i�O�̒l�ɂȂ��Ă��Ȃ����
		if(delta_time != current_time && delta_time < 1000)
		{
			//�Q�[���}�l�[�W���[�ŊǗ����Ă���f���^�^�C�����X�V
			CGameManager::GetInstance().SetDeltaTime(delta_time);
		}

		//�Q�[���t���[
		mGame->Input();
		mGame->Update();
		mGame->Render();

		int64_t sleep_time = 16666 - delta_time;

		if(sleep_time > 0)
		{
			float tt = sleep_time / 1000.0f;

			//�w�肵�����Ύ��Ԃ������X���b�h���u���b�N���� (function template)
			std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(tt)));
		}
	}

	//�^�C�}�𑜓x�����ɖ߂�
	::timeEndPeriod(1);

	DX11SetTransform::GetInstance()->Uninit();

	//�������
	CDirectXGraphics::GetInstance()->Exit();

	return window->GetMessage();
}