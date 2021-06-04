#include "CActor.h"

CActor::CActor(CLevel& owner):mOwnerInterface(owner)
{}

void CActor::AddComponent(CComponent& component)
{
	int myPriority = component.GetPriority();
	auto itr = this->mComponents.begin();

	for(; itr != this->mComponents.end(); ++itr)
	{
		if(myPriority < (*itr)->GetPriority())
		{
			break;
		}
	}

	this->mComponents.emplace(itr , component);
}

void CActor::Update()
{
	for(auto& component : mComponents)
	{
		component->Update();
	}
}

void CActor::Destroy()
{
	mOwnerInterface.DestroyActor(*this);
}