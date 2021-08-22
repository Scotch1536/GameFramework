#include "../Level/CLevel.h"
#include "../Interfaces/IRender.h"
#include "../Managers/CInputManager.h"

#include "CActor.h"

CActor::CActor(ILevel& owner, bool isAffectToPause)
	:CObject("Actor"),
	mOwnerInterface(owner), mIsAffectToPause(isAffectToPause),
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

	for (; itr != this->mComponents.end(); ++itr)
	{
		if ((*itr).get() == &component)return;
		if (myPriority < (*itr)->GetPriority())
		{
			break;
		}
	}
	this->mComponents.emplace(itr, &component);
}

void CActor::AddRenderComponent(IRender& component)
{
	mRenderComponents.emplace_back(&component);
}

void CActor::RequestAddAlphaRenderComponentToLevel(IRender& renderTarget, bool isFront)
{
	mOwnerInterface.AddAlphaRenderComponent(renderTarget, isFront);
}

void CActor::RequestAdd2DRenderComponentToLevel(IRender& renderTarget)
{
	mOwnerInterface.Add2DRenderComponent(renderTarget);
}

void CActor::RequestAddDoAfterUpdateFunction(const std::function<void()>& func)
{
	AddDoAfterUpdateFunction(func);
}

void CActor::Update()
{
	Transform.Update();

	for(auto& component : mComponents)
	{
		component->Update();
	}

	//UpdateŒã‚És‚¤ŠÖ”‚ðŽÀs
	if (mDoAfterUpdateFunction.size() != 0)
	{
		for (auto& func : mDoAfterUpdateFunction)
		{
			func();
		}
		//’†g‚ð‹ó‚É‚·‚é
		mDoAfterUpdateFunction.clear();
		mDoAfterUpdateFunction.shrink_to_fit();
	}
}

void CActor::Render()
{
	for (auto& renderComp : mRenderComponents)
	{
		renderComp->Render();
	}
}

void CActor::Destroy()
{
	mOwnerInterface.DestroyActor(*this);
}