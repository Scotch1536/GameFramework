#include "../Level/CLevel.h"
#include "../Interfaces/IRender.h"
#include "../Managers/CInputManager.h"

#include "CActor.h"

CActor::CActor(ILevel& owner , bool isAffectToPause)
	:CObject("Actor") ,
	mOwnerInterface(owner) , mIsAffectToPause(isAffectToPause) ,
	Transform(*this)
{
	mOwnerInterface.AddActor(*this);
}

CActor::~CActor()
{
	CInputManager::GetInstance().ReleaseBindTarget(*this);
}

void CActor::AddComponent(CComponent& component)
{
	int myPriority = component.GetPriority();
	auto itr = this->mComponents.begin();

	for(; itr != this->mComponents.end(); ++itr)
	{
		if((*itr).get() == &component)return;
		if(myPriority < (*itr)->GetPriority())
		{
			break;
		}
	}
	this->mComponents.emplace(itr , &component);
}

void CActor::AddRenderComponent(IRender& component)
{
	mRenderComponents.emplace_back(&component);
}

void CActor::RequestAddAlphaRenderComponentToLevel(IRender& renderTarget)
{
	mOwnerInterface.AddAlphaRenderComponent(renderTarget);
}

void CActor::Update()
{
	for(auto& component : mComponents)
	{
		component->Update();
	}
}

void CActor::Render()
{
	for(auto& renderComp : mRenderComponents)
	{
		renderComp->Render();
	}
}

void CActor::Destroy()
{
	mOwnerInterface.DestroyActor(*this);
}