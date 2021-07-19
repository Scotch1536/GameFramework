#include <Windows.h>

#include "../DebugTools/imgui/myimgui.h"
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/CDirectInput.h"
#include "../Managers/CInputManager.h"
#include "../Managers/CSoundManager.h"

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

	//�T�E���h�}�l�[�W���[������
	CSoundManager::GetInstance();

	CDirectXGraphics* directGraph = CDirectXGraphics::GetInstance();

	sts = directGraph->Init(
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
	directGraph->TurnOnAlphaBlending();

	//DIRECTINPUT������
	CDirectInput::GetInstance().Init
	(
		mApp.GetHInst() ,
		mApp.GetHWnd() ,
		CApplication::CLIENT_WIDTH ,
		CApplication::CLIENT_HEIGHT
	);

	//�R���X�^���g�o�b�t�@�쐬
	sts = CreateConstantBuffer(directGraph->GetDXDevice() , sizeof(ConstantBufferViewPort) , mConstantBufferViewPort.GetAddressOf());
	if(!sts)
	{
		MessageBox(NULL , "CreateBuffer(constant buffer Light) error" , "Error" , MB_OK);
	}

	ID3D11DeviceContext* devCon = directGraph->GetImmediateContext();
	ConstantBufferViewPort cb;

	cb.ScreenWidth = CApplication::CLIENT_WIDTH;
	cb.ScreenHeight = CApplication::CLIENT_HEIGHT;

	devCon->UpdateSubresource(mConstantBufferViewPort.Get() , 0 , nullptr , &cb , 0 , 0);

	devCon->VSSetConstantBuffers(5 , 1 , mConstantBufferViewPort.GetAddressOf());
	devCon->PSSetConstantBuffers(5 , 1 , mConstantBufferViewPort.GetAddressOf());

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

	if(mLoadLevelFunction != nullptr)
	{
		mLoadLevelFunction();
		mLoadLevelFunction = nullptr;
	}
}

void CGame::LoadLevel(CLevel& level)
{
	auto loadLevel = [&]
	{
		mLevel.reset(&level);

		mLevel->Init();
	};
	mLoadLevelFunction = loadLevel;
}