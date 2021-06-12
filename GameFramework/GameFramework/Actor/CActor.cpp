#include "../Level/CLevel.h"
#include "../Interfaces/IRender.h"
#include "../Managers/CInputManager.h"

#include "CActor.h"

CActor::CActor(CLevel& owner):mOwnerInterface(owner)
{
	static_cast<ILevelToActor&>(owner).AddActor(*this);
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

void CActor::RegisterRenderComponent(IRender& component)
{
	mRenderAttributeComponents.emplace_back(&component);
}

CTransform& CActor::GetTransform()
{
	return mTransform;
}

void CActor::Update()
{
	if(!mTransform.GetIsChild())mTransform.Update();

	for(auto& component : mComponents)
	{
		component->Update();
	}
}

void CActor::Render()
{
	for(auto& renderComp : mRenderAttributeComponents)
	{
		renderComp->Render();
	}
}

void CActor::Destroy()
{
	mOwnerInterface.DestroyActor(*this);
}

bool CActor::GetComponentFromAttribute(CComponent::EAttribute attribute , CComponent*& result)const
{
	for(auto& component : mComponents)
	{
		if(component->GetAttribute() == attribute)
		{
			result = component.get();
			return true;
		}
	}
	return false;
}
