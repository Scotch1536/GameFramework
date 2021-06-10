#include "CLevel.h"
#include "CGame.h"
#include "CGameManager.h"
#include "CCameraComponent.h"
#include "DX11Settransform.h"

CLevel::CLevel(CGame& owner):mOwnerInterface(&owner)
{
	mOwnerInterface->LoadLevel(*this);
}

CLevel::CLevel(IGameManagerToLevel& receiver)
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
	for(auto& actor : mActors)
	{
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

	CDirectXGraphics::GetInstance()->GetSwapChain()->Present(0 , 0);
}

void CLevel::DestroyActor(CActor& target)
{
	//�����_�����쐬
	auto destroyLambda = [&]
	{
		CComponent* refCamera;

		if(target.GetComponentFromAttribute(CComponent::EAttribute::CAMERA , refCamera))
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