#include <Windows.h>

#include "CGame.h"
#include "Application.h"
#include "CDirectInput.h"
#include "CDirectXGraphics.h"
#include "DX11Settransform.h"
#include "CInputManager.h"

CGame::CGame(CGameManager& partner)
{}

long CGame::Execute(HINSTANCE hInst , int winMode)
{
	// �A�v���P�[�V������������
	mApp.reset(new Application(*this));
	mApp->Init(hInst);

	// �E�C���h�E��\������
	ShowWindow(mApp->GetHWnd() , winMode);
	UpdateWindow(mApp->GetHWnd());

	Init();

	// ���C�����[�v
	long ret = mApp->MainLoop();

	// �A�v���P�[�V�����I������
	mApp->Dispose();

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
		mApp->GetHWnd() ,
		Application::CLIENT_WIDTH ,
		Application::CLIENT_HEIGHT ,
		false);
	if(!sts)
	{
		MessageBox(mApp->GetHWnd() , "DX11 init error" , "error" , MB_OK);
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
		mApp->GetHInst() ,
		mApp->GetHWnd() ,
		Application::CLIENT_WIDTH ,
		Application::CLIENT_HEIGHT
	);

	if(mLevel != nullptr)
	{
		mLevel->Init();
	}
}

void CGame::Input(uint64_t deltataime)
{
	CInputManager::GetInstance().CheckInput();
}

void CGame::Update(uint64_t deltataime)
{
	mLevel->Update();
}

void CGame::Render(uint64_t deltataime)
{
	mLevel->Render();
}

void CGame::LoadLevel(CLevel& level)
{
	mLevel.reset(&level);

	mLevel->Init();
}