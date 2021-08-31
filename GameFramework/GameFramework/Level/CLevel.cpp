#include "../ExternalTools/imgui/myimgui.h"
#include "../ExternalCode/DX11Settransform.h"
#include "../Game/CGame.h"
#include "../Managers/CGameManager.h"
#include "../Managers/CColliderManager.h"
#include "../Managers/CInputManager.h"
#include "../Components/CCameraComponent.h"

#include "CLevel.h"

CLevel::CLevel(IGame& owner , bool isFeed , XMFLOAT3 feedColor , float oneFrameAlpha):CObject("Level") , mOwnerInterface(owner)
{
	mOwnerInterface.LoadLevel(*this , isFeed , feedColor , oneFrameAlpha);
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
	CActor* cameraActor = nullptr;

	//更新前に行う関数を実行
	if(mDoBeforeUpdateFunction.size() != 0)
	{
		for(auto& func : mDoBeforeUpdateFunction)
		{
			func();
		}
		//中身を空にする
		mDoBeforeUpdateFunction.clear();
		mDoBeforeUpdateFunction.shrink_to_fit();
	}

	//Tick前トランスフォーム更新処理
	for(auto& actor : mActors)
	{
		if(CGameManager::GetInstance().GetIsPause())
		{
			if(actor->GetIsAffectToPause())continue;
		}

		if(!actor->Transform.GetIsChild())actor->Transform.Update();
	}

	CColliderManager::GetInstance().Update();

	//カメラ所持のアクターのみ先に処理する
	if(mRenderingCamera != nullptr)
	{
		cameraActor = &mRenderingCamera->GetOwner();
		cameraActor->Tick();
		cameraActor->Update();
	}

	//Tick処理
	for(auto& actor : mActors)
	{
		if(actor.get() == cameraActor)continue;

		if(CGameManager::GetInstance().GetIsPause())
		{
			if(actor->GetIsAffectToPause())continue;
		}

		actor->Tick();
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

	// ターゲットバッファクリア
	CDirectXGraphics::GetInstance()->GetImmediateContext()->ClearRenderTargetView(
		CDirectXGraphics::GetInstance()->GetRenderTargetView() , col);
	// Zバッファクリア
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
		// 2D描画用射影変換行列
		XMFLOAT4X4 projectionMatrix2D = {
				2.0f / static_cast<float>(CApplication::CLIENT_WIDTH) , 0.0f , 0.0f , 0.0f ,
				0.0f , -2.0f / static_cast<float>(CApplication::CLIENT_HEIGHT), 0.0f , 0.0f ,
				0.0f , 0.0f , 1.0f , 0.0f ,
				-1.0f , 1.0f , 0.0f , 1.0f
		};

		DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION , projectionMatrix2D);

		if(m2DTranslucentRenderComponents.size() != 0)
		{
			for(auto& alphaRender : m2DTranslucentRenderComponents)
			{
				alphaRender->Render();
			}
			m2DTranslucentRenderComponents.clear();
			m2DTranslucentRenderComponents.shrink_to_fit();
		}

		if(m2DOpacityRenderComponents.size() != 0)
		{
			for(auto& render : m2DOpacityRenderComponents)
			{
				render->Render();
			}
			m2DOpacityRenderComponents.clear();
			m2DOpacityRenderComponents.shrink_to_fit();
		}
	}

	//ImGuiに渡す描画の関数オブジェクト一つの関数オブジェクトにまとめる
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
	//ラムダ式を作成
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

	//作成したラムダ式を格納
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