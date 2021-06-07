#include "CLevel.h"
#include "CGame.h"
#include "CCameraComponent.h"
#include "DX11Settransform.h"

CLevel::CLevel(CGame& owner):mOwnerInterface(owner)
{
	mOwnerInterface.LoadLevel(*this);
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
}

void CLevel::Render()
{
	XMFLOAT4X4 bufMTX;

	if(mRenderingCamera == nullptr)
	{
		MessageBox(NULL , "Not Found RenderingCamera" , "error" , MB_OK);
		exit(1);
	}

	bufMTX = mRenderingCamera->GetProjectionMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::PROJECTION , bufMTX);

	bufMTX = mRenderingCamera->GetCameraMatrix();
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::VIEW , bufMTX);

	for(auto& actor : mActors)
	{
		actor->Render();
	}
}

void CLevel::DestroyActor(CActor& target)
{
	for(auto itr = mActors.begin(); itr != mActors.end(); ++itr)
	{
		if((*itr).get() == &target)
		{
			mActors.erase(itr);
			break;
		}
	}
	mActors.shrink_to_fit();
}