#include "../DebugTools/imgui/myimgui.h"
#include "../ExternalCode/DX11Settransform.h"
#include "../Game/CGame.h"
#include "../Managers/CGameManager.h"
#include "../Managers/CColliderManager.h"
#include "../Components/CCameraComponent.h"

#include "CLevel.h"

CLevel::CLevel(IGame& owner):CObject("Level") , mOwnerInterface(&owner)
{
	mOwnerInterface->LoadLevel(*this);
}

CLevel::CLevel(IGameManagerToLevel& receiver) : CObject("Level")
{
	receiver.SetStartLevel(*this);
}

void CLevel::AddActor(CActor& actor)
{
	mActors.emplace_back(&actor);
}

void CLevel::RequestSetCamera(CCameraComponent& camera)
{
	mRenderingCamera = &camera;
}

void CLevel::RequestLoadLevel(CLevel& level)
{
	mOwnerInterface->LoadLevel(level);
}

void CLevel::Update()
{
	CActor* cameraActor = nullptr;

	//Tick�O�g�����X�t�H�[���X�V����
	for(auto& actor : mActors)
	{
		if(CGameManager::GetInstance().GetIsPause())
		{
			if(actor->GetIsAffectToPause())continue;
		}

		if(!actor->Transform.GetIsChild())actor->Transform.Update();
	}

	CColliderManager::GetInstance().Update();

	//�J���������̃A�N�^�[�̂ݐ�ɏ�������
	if(mRenderingCamera != nullptr)
	{
		cameraActor = &mRenderingCamera->GetOwner();
		cameraActor->Tick();
		cameraActor->Update();
	}

	//Tick����
	for(auto& actor : mActors)
	{
		if(actor.get() == cameraActor)continue;

		if(CGameManager::GetInstance().GetIsPause())
		{
			if(actor->GetIsAffectToPause())continue;
		}

		actor->Tick();
	}

	//Tick��ɍs���֐������s
	if(mDoAfterTickFunction.size() != 0)
	{
		for(auto& func : mDoAfterTickFunction)
		{
			func();
		}
		//���g����ɂ���
		mDoAfterTickFunction.clear();
		mDoAfterTickFunction.shrink_to_fit();
	}

	for(auto& actor : mActors)
	{
		if(actor.get() == cameraActor)continue;

		if(CGameManager::GetInstance().GetIsPause())
		{
			if(actor->GetIsAffectToPause())continue;
		}

		actor->Update();
	}
}

void CLevel::Render()
{
	XMFLOAT4X4 bufMTX;

	if(mRenderingCamera == nullptr)
	{
		MessageBox(NULL , "Not Found RenderingCamera" , "error" , MB_OK);
		exit(1);
	}

	float col[4] = { 0.f,0.f,1.f,1.f };

	// �^�[�Q�b�g�o�b�t�@�N���A
	CDirectXGraphics::GetInstance()->GetImmediateContext()->ClearRenderTargetView(
		CDirectXGraphics::GetInstance()->GetRenderTargetView() , col);
	// Z�o�b�t�@�N���A
	CDirectXGraphics::GetInstance()->GetImmediateContext()->ClearDepthStencilView(
		CDirectXGraphics::GetInstance()->GetDepthStencilView() ,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL , 1.0f , 0);

	bufMTX = mRenderingCamera->GetProjectionMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION , bufMTX);

	bufMTX = mRenderingCamera->GetViewMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW , bufMTX);


	for(auto& actor : mActors)
	{
		actor->Render();
	}

	if(mAlphaRenderComponents.size() != 0)
	{
		for(auto& alphaRender : mAlphaRenderComponents)
		{
			alphaRender->Render();
		}
		mAlphaRenderComponents.clear();
		mAlphaRenderComponents.shrink_to_fit();
	}

	if(m2DRenderComponents.size() != 0)
	{
		// 2D�`��p�ˉe�ϊ��s��
		XMFLOAT4X4 projectionMatrix2D = {
				2.0f / static_cast<float>(CApplication::CLIENT_WIDTH) , 0.0f , 0.0f , 0.0f ,
				0.0f , -2.0f / static_cast<float>(CApplication::CLIENT_HEIGHT), 0.0f , 0.0f ,
				0.0f , 0.0f , 1.0f , 0.0f ,
				-1.0f , 1.0f , 0.0f , 1.0f
		};

		DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION , projectionMatrix2D);

		for(auto& render : m2DRenderComponents)
		{
			render->Render();
		}
		m2DRenderComponents.clear();
		m2DRenderComponents.shrink_to_fit();
	}

	//ImGui�ɓn���`��̊֐��I�u�W�F�N�g��̊֐��I�u�W�F�N�g�ɂ܂Ƃ߂�
	auto allGuiMethodExecute = [&]
	{
		for(auto& guiMethod : mImGuiDrawMethod)
		{
			guiMethod();
		}
	};

#ifdef _DEBUG
	imguiDraw(allGuiMethodExecute);
#endif

	mImGuiDrawMethod.clear();
	mImGuiDrawMethod.shrink_to_fit();

	CDirectXGraphics::GetInstance()->GetSwapChain()->Present(0 , 0);
}

void CLevel::DestroyActor(CActor& target)
{
	//�����_�����쐬
	auto destroyLambda = [&]
	{
		CComponent* refCamera;

		if(target.GetComponent<CCameraComponent>(refCamera))
		{
			if(refCamera == mRenderingCamera)mRenderingCamera = nullptr;
		}

		for(auto itr = mActors.begin(); itr != mActors.end(); ++itr)
		{
			if((*itr).get() == &target)
			{
				mActors.erase(itr);
				mActors.shrink_to_fit();
				break;
			}
		}
	};

	//�쐬���������_�����i�[
	mDoAfterTickFunction.emplace_back(destroyLambda);
}

void CLevel::SetOwnerInterface(CGame& owner)
{
	mOwnerInterface = &owner;
}

const XMFLOAT4X4* CLevel::GetRenderingCameraViewMatrix()const
{
	if(mRenderingCamera == nullptr)
	{
		return nullptr;
	}
	else
	{
		return &mRenderingCamera->GetViewMatrix();
	}
}