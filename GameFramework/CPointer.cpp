#include "CPointer.h"
#include "CFighter.h"
#include "GameFramework/Components/CBillboardComponent.h"
#include "GameFramework/Game/CApplication.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/ExternalTools/imgui/myimgui.h"
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Game/CApplication.h"

CPointer::CPointer(ILevel& partner , CFighter& owner):CActor(partner) , mOwner(owner)
{
	int displayCenterPosX = GetSystemMetrics(SM_CXSCREEN) / 2;
	int displayCenterPosY = GetSystemMetrics(SM_CYSCREEN) / 2;

	SetCursorPos(displayCenterPosX , displayCenterPosY);
	mInitMousePosX = CApplication::CLIENT_WIDTH / 2;
	mInitMousePosY = CApplication::CLIENT_HEIGHT / 2;

	CBillboardComponent& billboard = *new CBillboardComponent(*this , Transform , "Assets/Textures/Pointer/Pointer.png");
	billboard.Transform.Scale = { 10.0f,10.0f,1.0f };
}

void CPointer::Tick()
{
	if(mInitLocation == nullptr)
	{
		mInitLocation.reset(new XMFLOAT3);
		*mInitLocation = mOwner.Transform.Location;
	}

	float mousePosX = CInputManager::GetInstance().GetMousePosX();
	float mousePosY = CInputManager::GetInstance().GetMousePosY();

	mDiffPosX = mInitMousePosX - mousePosX;
	mDiffPosY = mInitMousePosY - mousePosY;

	float posX , posY;
	posX = mDiffPosX / 6.f;
	posY = mDiffPosY / 6.f;

	Transform.Location.x = mInitLocation->x - posX;
	Transform.Location.y = mInitLocation->y + posY;
}