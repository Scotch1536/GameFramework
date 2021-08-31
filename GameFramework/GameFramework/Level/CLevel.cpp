#include <algorithm>

#include "../ExternalTools/imgui/myimgui.h"
#include "../ExternalCode/DX11Settransform.h"
#include "../Game/CGame.h"
#include "../Managers/CGameManager.h"
#include "../Managers/CColliderManager.h"
#include "../Managers/CInputManager.h"
#include "../Components/CCameraComponent.h"

#include "CLevel.h"

CLevel::CLevel(IGame& owner , bool isFeed , XMFLOAT3 feedColor , float FeedTime):CObject("Level") , mOwnerInterface(owner)
{
	mOwnerInterface.LoadLevel(*this , isFeed , feedColor , FeedTime);
}

CLevel::~CLevel()
{
	CInputManager::GetInstance().ReleaseBindTarget(*this);
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
	//�X�V�O�ɍs���֐������s
	if(mDoBeforeUpdateFunction.size() != 0)
	{
		for(auto& func : mDoBeforeUpdateFunction)
		{
			func();
		}
		//���g����ɂ���
		mDoBeforeUpdateFunction.clear();
		mDoBeforeUpdateFunction.shrink_to_fit();
	}

	std::vector<CActor*> actors;
	CActor* cameraActor = nullptr;

	if(CGameManager::GetInstance().GetIsPause())
	{
		for(auto& actor : mActors)
		{
			if(!actor->GetIsAffectToPause())
			{
				actors.emplace_back(actor.get());
			}
		}
	}
	else
	{
		for(auto& actor : mActors)
		{
			actors.emplace_back(actor.get());
		}
	}

	//Tick�O�g�����X�t�H�[���X�V����
	for(auto& actor : actors)
	{
		if(!actor->Transform.GetIsChild())actor->Transform.Update();
	}

	//�R���W�����}�l�[�W���[�̍X�V
	CColliderManager::GetInstance().Update();

	//�J���������̃A�N�^�[�̂ݐ�ɏ�������
	if(mRenderingCamera != nullptr)
	{
		cameraActor = &mRenderingCamera->GetOwner();

		auto cameraActorItr = std::find(actors.begin() , actors.end() , cameraActor);
		if(cameraActorItr != actors.end())
		{
			cameraActor->Tick();
			cameraActor->Update();

			actors.erase(cameraActorItr);
			actors.shrink_to_fit();
		}
	}

	//Tick����
	for(auto& actor : actors)
	{
		actor->Tick();
	}

	//�X�V����
	for(auto& actor : actors)
	{
		actor->Update();
	}
}

void CLevel::RequestRenderOrders(std::vector<SRenderInfo>& renderOrders)
{
	for(auto& renderOrder : renderOrders)
	{
		if(renderOrder.RenderOption == ERenderOption::OPACITY3D)Add3DOpacityRenderComponent(renderOrder.RenderComponentReference);
		else if(renderOrder.RenderOption == ERenderOption::TRANSLUCENT3D)Add3DTranslucentRenderComponent(renderOrder.RenderComponentReference);
		else if(renderOrder.RenderOption == ERenderOption::BILLBOARD)Add3DTranslucentRenderComponent(renderOrder.RenderComponentReference , true);
		else if(renderOrder.RenderOption == ERenderOption::OPACITY2D)Add2DOpacityRenderComponent(renderOrder.RenderComponentReference);
		else if(renderOrder.RenderOption == ERenderOption::TRANSLUCENT2D)Add2DTranslucentRenderComponent(renderOrder.RenderComponentReference);
	}
	renderOrders.clear();
	renderOrders.shrink_to_fit();
}

void CLevel::Render()
{
	XMFLOAT4X4 bufMTX;

	float col[4] = { 0.f,0.f,1.f,1.f };

	// �^�[�Q�b�g�o�b�t�@�N���A
	CDirectXGraphics::GetInstance()->GetImmediateContext()->ClearRenderTargetView(
		CDirectXGraphics::GetInstance()->GetRenderTargetView() , col);
	// Z�o�b�t�@�N���A
	CDirectXGraphics::GetInstance()->GetImmediateContext()->ClearDepthStencilView(
		CDirectXGraphics::GetInstance()->GetDepthStencilView() ,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL , 1.0f , 0);

	if(mRenderingCamera != nullptr)
	{
		bufMTX = mRenderingCamera->GetProjectionMatrix();
		DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION , bufMTX);

		bufMTX = mRenderingCamera->GetViewMatrix();
		DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW , bufMTX);
	}

	for(auto& actor : mActors)
	{
		actor->Render();
	}

	if(m3DOpacityRenderComponents.size() != 0)
	{
		for(auto& alphaRender : m3DOpacityRenderComponents)
		{
			alphaRender->Render();
		}
		m3DOpacityRenderComponents.clear();
		m3DOpacityRenderComponents.shrink_to_fit();
	}

	if(m3DTranslucentRenderComponents.size() != 0)
	{
		for(auto& alphaRender : m3DTranslucentRenderComponents)
		{
			alphaRender->Render();
		}
		m3DTranslucentRenderComponents.clear();
		m3DTranslucentRenderComponents.shrink_to_fit();
	}

	if(m2DOpacityRenderComponents.size() != 0 || m2DTranslucentRenderComponents.size() != 0)
	{
		// 2D�`��p�ˉe�ϊ��s��
		XMFLOAT4X4 projectionMatrix2D = {
				2.0f / static_cast<float>(CApplication::CLIENT_WIDTH) , 0.0f , 0.0f , 0.0f ,
				0.0f , -2.0f / static_cast<float>(CApplication::CLIENT_HEIGHT), 0.0f , 0.0f ,
				0.0f , 0.0f , 1.0f , 0.0f ,
				-1.0f , 1.0f , 0.0f , 1.0f
		};

		DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION , projectionMatrix2D);

		CDirectXGraphics::GetInstance()->TurnOffZbuffer();

		if(m2DOpacityRenderComponents.size() != 0)
		{
			for(auto& render : m2DOpacityRenderComponents)
			{
				render->Render();
			}
			m2DOpacityRenderComponents.clear();
			m2DOpacityRenderComponents.shrink_to_fit();
		}

		if(m2DTranslucentRenderComponents.size() != 0)
		{
			for(auto& alphaRender : m2DTranslucentRenderComponents)
			{
				alphaRender->Render();
			}
			m2DTranslucentRenderComponents.clear();
			m2DTranslucentRenderComponents.shrink_to_fit();
		}

		CDirectXGraphics::GetInstance()->TurnOnZBuffer();
	}

	//ImGui�ɓn���`��̊֐��I�u�W�F�N�g��̊֐��I�u�W�F�N�g�ɂ܂Ƃ߂�
	auto allGuiMethodExecute = [&]
	{
		for(auto& guiMethod : mImGuiDrawFunction)
		{
			guiMethod();
		}
	};
	imguiDraw(allGuiMethodExecute);

	mImGuiDrawFunction.clear();
	mImGuiDrawFunction.shrink_to_fit();

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
	mDoBeforeUpdateFunction.emplace_back(destroyLambda);
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