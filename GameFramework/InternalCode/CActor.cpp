#include "CActor.h"
#include "CLevel.h"
#include "IRender.h"

CActor::CActor(CLevel& owner):mOwnerInterface(owner)
{
	owner.AddActor(*this);
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

void CActor::Update()
{
	for(auto& component : mComponents)
	{
		/*	if(mShouldCheckAttribute)
			{
				int inheritInterface = component->GetInheritInterface();

				if(inheritInterface&static_cast<int>(CComponent::InheritInteface::RENDER))
				{
					int componentType = component->GetType();

					if(componentType&static_cast<int>(CComponent::ComponentType::SMESH)
					{
						dynamic_cast<CStaticMeshComponent>component
					}
					mRenderAttributeComponents.push_back(static_cast<IRender&>(dynamic_cast<CStaticMeshComponent&>(*component)));
				}
			}*/
		component->Update();
	}


	if(mShouldCheckAttribute)mShouldCheckAttribute = false;
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

bool CActor::GetComponentFromAttribute(CComponent::EAttribute attribute , CComponent* inOut)const
{
	for(auto& component : mComponents)
	{
		if(component->GetAttribute() == attribute)
		{
			inOut = component.get();
			return true;
		}
	}
	return false;
}
