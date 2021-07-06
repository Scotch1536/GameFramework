#include "../DebugTools/imgui/myimgui.h"
#include "../ExternalCode/DX11Settransform.h"
#include "../Game/CGame.h"
#include "../Managers/CGameManager.h"
#include "../Managers/CColliderManager.h"
#include "../Components/CCameraComponent.h"

#include "CLevel.h"

CLevel::CLevel(CGame& owner):CObject("Level") , mOwnerInterface(&owner)
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

void CLevel::Update()
{
	CColliderManager::GetInstance().Update();

	for(auto& actor : mActors)
	{
		if(CGameManager::GetInstance().GetIsPause())
		{
			if(actor->GetIsAffectToPause())continue;
		}

		if(!actor->Transform.GetIsChild())actor->Transform.Update();
	}

	for(auto& actor : mActors)
	{
		if(CGameManager::GetInstance().GetIsPause())
		{
			if(actor->GetIsAffectToPause())continue;
		}

		actor->Tick();
		actor->Update();
	}

	//�X�V��ɍs���֐������s
	for(auto& func : mDoAfterUpdateFunction)
	{
		func();
	}

	//���g����ɂ���
	mDoAfterUpdateFunction.clear();
	mDoAfterUpdateFunction.shrink_to_fit();
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

	for(auto& alphaRender : mAlphaRenderComponents)
	{
		alphaRender->Render();
	}
	mAlphaRenderComponents.clear();
	mAlphaRenderComponents.shrink_to_fit();

	//ImGui�ɓn���`��̊֐��I�u�W�F�N�g��̊֐��I�u�W�F�N�g�ɂ܂Ƃ߂�
	auto allGuiMethodExecute = [&]
	{
		for(auto& guiMethod : mImGuiDrawMethod)
		{
			guiMethod();
		}
	};

	imguiDraw(allGuiMethodExecute);
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
	mDoAfterUpdateFunction.emplace_back(destroyLambda);
}

void CLevel::SetOwnerInterface(CGame& owner)
{
	mOwnerInterface = &owner;
}