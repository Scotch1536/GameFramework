#include <Windows.h>

#include "CGame.h"
#include "Application.h"
#include "CDirectInput.h"
#include "CDirectXGraphics.h"
#include "DX11Settransform.h"


CGame::CGame()
{}

CGame& CGame::GetInstance()
{
	static CGame instance;

	return instance;
}

long CGame::Execute(HINSTANCE hInst , int winMode)const
{
	// �A�v���P�[�V������������
	Application* App = Application::Instance();		// �C���X�^���X�擾
	App->Init(hInst);

	// �E�C���h�E��\������
	ShowWindow(App->GetHWnd() , winMode);
	UpdateWindow(App->GetHWnd());

	// ���C�����[�v
	long ret = App->MainLoop();

	// �A�v���P�[�V�����I������
	App->Dispose();

	return ret;
}

void CGame::Init()
{
	// DX11�@������
	bool sts;

	sts = CDirectXGraphics::GetInstance()->Init(
		Application::Instance()->GetHWnd() ,
		Application::CLIENT_WIDTH ,
		Application::CLIENT_HEIGHT ,
		false);
	if(!sts)
	{
		MessageBox(Application::Instance()->GetHWnd() , "DX11 init error" , "error" , MB_OK);
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
		Application::Instance()->GetHInst() ,
		Application::Instance()->GetHWnd() ,
		Application::CLIENT_WIDTH ,
		Application::CLIENT_HEIGHT
	);
}

void CGame::Input(uint64_t deltataime)
{

}

void CGame::Update(uint64_t deltataime)
{

}

void CGame::Render(uint64_t deltataime)
{

}

void CGame::LoadLevel(CLevel& level)
{
	mLevel.reset(&level);
}