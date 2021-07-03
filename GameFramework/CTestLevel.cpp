#include <string>

#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CLightComponent.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CGameManager.h"
#include "GameFramework/DebugTools/imgui/myimgui.h"

#include "CTestLevel.h"
#include "CDice.h"
#include "CTestCharacter.h"
#include "CSkyDome.h"

void CTestLevel::Init()
{
	CDice& dice = *new CDice(*this);

	dice.Transform.Location = { 0.f,40.f,0.f };

	/*
	レベルから指定のアクターインスタンスのメソッドをインプットマネージャーにバインドすることは可能
	アクターからでもレベルからでもどちらでも可能だ
	*/
	//CInputManager::GetInstance().AddAction("XP" , EButtonOption::PRESS , dice , { EButtonType::KEYBOARD,DIK_S } , std::bind(&CDice::Rot , std::ref(dice) , 0));

	CTestCharacter& testChara = *new CTestCharacter(*this);
	//testChara.Transform.Rotation.Angle.z = 180.f;
	//testChara.Transform.Rotation.Angle.y = 180.f;

	//testChara.Transform.AttachTransform(dice.Transform);

	CSkyDome& skyDome = *new CSkyDome(*this);

	CComponent* buf = nullptr;
	//std::vector<CComponent*> buf2;
	//if(testChara.GetComponentFromAttribute(CComponent::EAttribute::CAMERA , buf))
	//{
	//	CCameraComponent& camera = dynamic_cast<CCameraComponent&>(*buf);
	//	this->RequestSetCamera(camera);
	//}

	if(testChara.GetComponent<CCameraComponent>(buf))
	{
		CCameraComponent& camera = dynamic_cast<CCameraComponent&>(*buf);
		this->RequestSetCamera(camera);
	}
	//if(testChara.GetAllComponents<CCameraComponent>(buf2))
	//{
	//	for(auto& buf : buf2)
	//	{
	//		buf->GetPriority();
	//	}
	//}
}

void CTestLevel::Tick()
{
	mCnt++;

	int64_t dt = CGameManager::GetInstance().GetDeltaTime();
	if(dt != 0)
	{
		mTime += static_cast<float>(dt / 1000.0f);
		//mTime = std::floorf(mTime * 100.0f) / 100.0f;
	}

	auto displayCount = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(10 , 10) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(200 , 200) , ImGuiCond_Once);

		ImGui::Begin(u8"カウント");

		ImGui::Text(std::to_string(mCnt).c_str());

		ImGui::End();
	};

	auto displayTime = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(10 , 220) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(200 , 200) , ImGuiCond_Once);

		ImGui::Begin(u8"時間");

		std::string buf = std::to_string(mTime);
		ImGui::Text(std::to_string(mTime).c_str());

		ImGui::End();
	};

	AddImGuiDrawMethod(displayCount);
	AddImGuiDrawMethod(displayTime);
}