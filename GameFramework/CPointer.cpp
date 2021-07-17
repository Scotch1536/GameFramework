#include "CPointer.h"
#include "CFighter.h"
#include "GameFramework/Components/CBillboardComponent.h"
#include "GameFramework/Game/CApplication.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/DebugTools/imgui/myimgui.h"
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
	billboard.Transform.Scale = { 5.0f,5.0f,1.0f };
	//billboard.Transform.Rotation.SetAngle({ 0.0f,0.0f,50.0f });
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

	auto displayPointer = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(CApplication::CLIENT_WIDTH - 210 , 10) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(200 , 200) , ImGuiCond_Once);

		ImGui::Begin(u8"ポインター情報");
		std::string diff = u8"差分\n" + std::to_string(mDiffPosX) + "," + std::to_string(mDiffPosY);
		ImGui::Text(diff.c_str());

		XMFLOAT3 bufLoc = Transform.GetWorldLocation();
		std::string loc = u8"ワールド座標\n" + std::to_string(bufLoc.x) + "," + std::to_string(bufLoc.y) + "," + std::to_string(bufLoc.z);
		ImGui::Text("\n");
		ImGui::Text(loc.c_str());

		ImGui::End();
	};
	mOwnerInterface.AddImGuiDrawMethod(displayPointer);
}