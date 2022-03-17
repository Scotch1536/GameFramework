//!
//!	@file
//!	@brief レベルシステムのソースファイル
//!

#include <algorithm>

#include "../ExternalTools/imgui/myimgui.h"
#include "../ExternalCode/DX11Settransform.h"
#include "../Game/CGame.h"
#include "../Managers/CGameManager.h"
#include "../Managers/CColliderManager.h"
#include "../Managers/CInputManager.h"
#include "../Managers/CLightManager.h"
#include "../Components/CCameraComponent.h"

#include "CLevel.h"

CLevel::CLevel(IGame& owner , bool isFeed , XMFLOAT3 feedColor , float FeedTime):CObject("Level") , mOwnerInterface(owner)
{
	//レベルをロードする
	mOwnerInterface.LoadLevel(*this , isFeed , feedColor , FeedTime);
}

CLevel::~CLevel()
{
	//インプットマネージャーと自身を切り離す
	CInputManager::GetInstance().ReleaseBind(*this);
}

void CLevel::AddActor(CActor& actor)
{
	mActors.emplace_back(&actor);
}

void CLevel::SetRenderCamera(CCameraComponent& camera)
{
	mRenderingCamera = &camera;
}

void CLevel::Update()
{
	//更新前に行うイベントを実行
	if(mDoBeforeUpdateEvents.size() != 0)
	{
		for(auto& event : mDoBeforeUpdateEvents)
		{
			event();
		}

		//中身を空にする
		mDoBeforeUpdateEvents.clear();
		mDoBeforeUpdateEvents.shrink_to_fit();
	}

	//デストロイイベントを実行
	if(mDestroyEvents.size() != 0)
	{
		for(auto& event : mDestroyEvents)
		{
			event();
		}

		//中身を空にする
		mDestroyEvents.clear();
		mDestroyEvents.shrink_to_fit();
	}

	std::vector<CActor*> actors;		//このフレームですべてを更新するアクター
	std::vector<CActor*> allActors;		//そのフレームでのUpdate開始時の全てのアクター
	CActor* cameraActor = nullptr;

	//処理するアクターの振り分け処理
	//ポーズ中なら
	if(CGameManager::GetInstance().GetIsPause())
	{
		for(auto& actor : mActors)
		{
			//ポーズの影響を受けないなら
			if(!actor->GetIsAffectToPause())
			{
				actors.emplace_back(actor.get());
			}
			allActors.emplace_back(actor.get());
		}
	}
	else
	{
		for(auto& actor : mActors)
		{
			actors.emplace_back(actor.get());
			allActors.emplace_back(actor.get());
		}
	}

	//Tick前トランスフォーム更新処理
	for(auto& actor : allActors)
	{
		if(!actor->Transform.GetIsChild())actor->Transform.Update();
	}

	//コリジョンマネージャーの更新
	CColliderManager::GetInstance().Update();

	//描画担当カメラを所持するアクターのみ先に処理する
	if(mRenderingCamera != nullptr)
	{
		cameraActor = &mRenderingCamera->GetOwner();

		//描画担当カメラを所持するアクターのイテレータを処理するアクターの配列から検索し取得
		auto cameraActorItr = std::find(actors.begin() , actors.end() , cameraActor);

		//取得できていれば
		if(cameraActorItr != actors.end())
		{
			//ポーズ中かつこのアクターがポーズの影響を受ける設定以外の全ての状態なら
			if(!(CGameManager::GetInstance().GetIsPause() && cameraActor->GetIsAffectToPause()))
			{
				cameraActor->Tick();
			}
			cameraActor->Update();

			actors.erase(cameraActorItr);
			actors.shrink_to_fit();
		}
	}

	//Tick処理
	for(auto& actor : actors)
	{
		actor->Tick();
	}

	//更新処理
	for(auto& actor : allActors)
	{
		actor->Update();
	}

	//ライトマネージャー更新
	CLightManager::GetInstance().Update();
}

void CLevel::RegisterRenderOrders(std::vector<SRenderInfo>& renderOrders)
{
	for(auto& renderOrder : renderOrders)
	{
		if(renderOrder.RenderOption == ERenderOption::OPAQUE3D)Add3DOpaqueRenderComponent(renderOrder.RenderComponentReference);
		else if(renderOrder.RenderOption == ERenderOption::TRANSLUCENT3D)Add3DTranslucentRenderComponent(renderOrder.RenderComponentReference , renderOrder.DistanceToCamera);
		else if(renderOrder.RenderOption == ERenderOption::BILLBOARD)Add3DTranslucentRenderComponent(renderOrder.RenderComponentReference , renderOrder.DistanceToCamera);
		else if(renderOrder.RenderOption == ERenderOption::OPAQUE2D)Add2DOpaqueRenderComponent(renderOrder.RenderComponentReference);
		else if(renderOrder.RenderOption == ERenderOption::TRANSLUCENT2D)Add2DTranslucentRenderComponent(renderOrder.RenderComponentReference);
	}

	renderOrders.clear();
	renderOrders.shrink_to_fit();
}

void CLevel::Render()
{
	XMFLOAT4X4 bufMTX;

	float col[4] = { 0.0f,0.0f,1.0f,1.0f };

	//ターゲットバッファクリア
	CDirectXGraphics::GetInstance()->GetImmediateContext()->ClearRenderTargetView(CDirectXGraphics::GetInstance()->GetRenderTargetView() , col);

	//Zバッファクリア
	CDirectXGraphics::GetInstance()->GetImmediateContext()->ClearDepthStencilView(CDirectXGraphics::GetInstance()->GetDepthStencilView() ,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL , 1.0f , 0);

	if(mRenderingCamera != nullptr)
	{
		//ビュー行列の取得&GPUへセット
		bufMTX = mRenderingCamera->GetViewMatrix();
		DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW , bufMTX);

		//プロジェクション行列の取得&GPUへセット
		bufMTX = mRenderingCamera->GetProjectionMatrix();
		DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION , bufMTX);
	}

	//アクターの描画メソッドを呼び出して描画命令を登録させる
	for(auto& actor : mActors)
	{
		actor->Render();
	}

	//描画命令登録から各種レンダーコンポーネントに割り振られたものを処理する
	if(m3DOpaqueRenderComponents.size() != 0)
	{
		for(auto& alphaRender : m3DOpaqueRenderComponents)
		{
			alphaRender->Render();
		}
		m3DOpaqueRenderComponents.clear();
		m3DOpaqueRenderComponents.shrink_to_fit();
	}

	if(m3DTranslucentRenderComponents.size() != 0)
	{
		//カメラから遠い順にソート
		std::sort(m3DTranslucentRenderComponents.begin() , m3DTranslucentRenderComponents.end() ,
			[](std::pair<IRender* , float>& lhs , std::pair<IRender* , float>& rhs)
			{
				return lhs.second > rhs.second;
			});

		for(auto& alphaRender : m3DTranslucentRenderComponents)
		{
			alphaRender.first->Render();
		}
		m3DTranslucentRenderComponents.clear();
		m3DTranslucentRenderComponents.shrink_to_fit();
	}

	if(m2DOpaqueRenderComponents.size() != 0 || m2DTranslucentRenderComponents.size() != 0)
	{
		//2D描画用射影変換行列
		XMFLOAT4X4 projectionMatrix2D = {
				2.0f / static_cast<float>(CApplication::CLIENT_WIDTH) , 0.0f , 0.0f , 0.0f ,
				0.0f , -2.0f / static_cast<float>(CApplication::CLIENT_HEIGHT), 0.0f , 0.0f ,
				0.0f , 0.0f , 1.0f , 0.0f ,
				-1.0f , 1.0f , 0.0f , 1.0f
		};

		//2D描画用射影変換行列をGPUにセット
		DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION , projectionMatrix2D);

		//Zバッファオフ
		CDirectXGraphics::GetInstance()->TurnOffZbuffer();

		if(m2DOpaqueRenderComponents.size() != 0)
		{
			for(auto& render : m2DOpaqueRenderComponents)
			{
				render->Render();
			}
			m2DOpaqueRenderComponents.clear();
			m2DOpaqueRenderComponents.shrink_to_fit();
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

		//Zバッファオン
		CDirectXGraphics::GetInstance()->TurnOnZBuffer();
	}

	//ImGuiに渡す描画のイベントを全て実行する関数オブジェクトを作成
	auto allGuiEventExecute = [&]
	{
		for(auto& guiEvent : mImGuiDrawEvents)
		{
			guiEvent();
		}
	};
	imguiDraw(allGuiEventExecute);

	mImGuiDrawEvents.clear();
	mImGuiDrawEvents.shrink_to_fit();

	CDirectXGraphics::GetInstance()->GetSwapChain()->Present(0 , 0);
}

void CLevel::DestroyActor(CActor& target)
{
	//デストロイ処理を行う関数オブジェクトを作成
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

	mDestroyEvents.emplace_back(destroyLambda);
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

XMFLOAT3 CLevel::GetRenderingCameraLocation()const
{
	XMFLOAT3 result;

	if(mRenderingCamera == nullptr)
	{
		result = { 0.0f,0.0f,0.0f };
	}
	else
	{
		XMFLOAT4X4 buf = mRenderingCamera->GetCameraTransMatrix();

		result.x = buf._41;
		result.y = buf._42;
		result.z = buf._43;
	}

	return result;
}