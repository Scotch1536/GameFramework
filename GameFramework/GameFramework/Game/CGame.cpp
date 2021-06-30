#include <Windows.h>

#include "../DebugTools/imgui/myimgui.h"
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/CDirectInput.h"
#include "../Managers/CInputManager.h"

#include "CGame.h"
#include "CApplication.h"

CGame::CGame(CGameManager& partner):mApp(*this)
{}

CGame::~CGame()
{
	imguiExit();
}

long CGame::Execute(HINSTANCE hInst , int winMode)
{
	// �A�v���P�[�V������������
	mApp.Init(hInst);

	// �E�C���h�E��\������
	ShowWindow(mApp.GetHWnd() , winMode);
	UpdateWindow(mApp.GetHWnd());

	Init();

	// ���C�����[�v
	long ret = mApp.MainLoop();

	// �A�v���P�[�V�����I������
	mApp.Dispose();

	return ret;
}

void CGame::SetLevel(CLevel& level)
{
	mLevel.reset(&level);
}

void CGame::Init()
{
	// DX11�@������
	bool sts;

	sts = CDirectXGraphics::GetInstance()->Init(
		mApp.GetHWnd() ,
		CApplication::CLIENT_WIDTH ,
		CApplication::CLIENT_HEIGHT ,
		false);
	if(!sts)
	{
		MessageBox(mApp.GetHWnd() , "DX11 init error" , "error" , MB_OK);
		exit(1);
	}

	sts = DX11SetTransform::GetInstance()->Init();
	if(!sts)
	{
		MessageBox(NULL , "SetTransform error" , "Error" , MB_OK);
		exit(1);
	}

	//�������ݒ�
	CDirectXGraphics::GetInstance()->TurnOnAlphaBlending();

	//DIRECTINPUT������
	CDirectInput::GetInstance().Init
	(
		mApp.GetHInst() ,
		mApp.GetHWnd() ,
		CApplication::CLIENT_WIDTH ,
		CApplication::CLIENT_HEIGHT
	);

	imguiInit();

	if(mLevel != nullptr)
	{
		mLevel->Init();
	}
}

void CGame::Input()
{
	CInputManager::GetInstance().CheckInput();
}

void CGame::Update()
{
	mLevel->Update();
	mLevel->Tick();
}

void CGame::Render()
{
	mLevel->Render();
}

void CGame::LoadLevel(CLevel& level)
{
	mLevel.reset(&level);

	mLevel->Init();
}