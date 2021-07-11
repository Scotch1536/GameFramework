#include "CPointer.h"
#include "CFighter.h"
#include "GameFramework/Components/CBillboardComponent.h"
#include "GameFramework/Game/CApplication.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/DebugTools/imgui/myimgui.h"
#include "GameFramework/Level/CLevel.h"

CPointer::CPointer(ILevel& partner , CFighter& owner):CActor(partner) , mOwner(owner)
{
	int displayCenterPosX = GetSystemMetrics(SM_CXSCREEN) / 2;
	int displayCenterPosY = GetSystemMetrics(SM_CYSCREEN) / 2;

	SetCursorPos(displayCenterPosX , displayCenterPosY);
	mInitMousePosX = CApplication::CLIENT_WIDTH / 2;
	mInitMousePosY = CApplication::CLIENT_HEIGHT / 2;

	CBillboardComponent& billboard = *new CBillboardComponent(*this , Transform , "Assets/Pointer/Pointer.png");
	billboard.Transform.Scale = { 5.0f,5.0f,1.0f };
}

void CPointer::Tick()
{
	float mousePosX = CInputManager::GetInstance().GetMousePosX();
	float mousePosY = CInputManager::GetInstance().GetMousePosY();

	mDiffPosX = mInitMousePosX - mousePosX;
	mDiffPosY = mInitMousePosY - mousePosY;

	float posX , posY;
	posX = mDiffPosX / 10.f;
	posY = mDiffPosY / 10.f;

	XMFLOAT3 forwardVec = mOwner.Transform.GetForwardVector();
	XMFLOAT3 RightVec = mOwner.Transform.GetRightVector();
	XMFLOAT3 UpwardVec = mOwner.Transform.GetUpwardVector();
	Transform.Location =
	{
		mOwner.Transform.Location.x + forwardVec.x*100.0f - RightVec.x*posX + UpwardVec.x*posY,
		mOwner.Transform.Location.y + forwardVec.y*100.0f - RightVec.y*posX + UpwardVec.y*posY,
		mOwner.Transform.Location.z + forwardVec.z*100.0f - RightVec.z*posX + UpwardVec.z*posY
	};

	auto displayPointer = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(1000 , 10) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(200 , 200) , ImGuiCond_Once);

		ImGui::Begin(u8"ポインター");
		std::string diff = u8"差分\n" + std::to_string(mDiffPosX) + "," + std::to_string(mDiffPosY);
		ImGui::Text(diff.c_str());
		ImGui::End();
	};
	mOwnerInterface.AddImGuiDrawMethod(displayPointer);

	mOwner.Rot();
}