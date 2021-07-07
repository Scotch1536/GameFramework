#include <string>

#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CLightComponent.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CGameManager.h"
#include "GameFramework/DebugTools/imgui/myimgui.h"
#include "GameFramework/Library/LCMath.h"

#include "CTestLevel.h"
#include "CDice.h"
#include "CFighter.h"
#include "CSkyDome.h"

void CTestLevel::Init()
{
	CDice& dice = *new CDice(*this);

	dice.Transform.Location = { 50.f,0.f,100.f };

	/*
	レベルから指定のアクターインスタンスのメソッドをインプットマネージャーにバインドすることは可能
	アクターからでもレベルからでもどちらでも可能だ
	*/
	//CInputManager::GetInstance().AddAction("XP" , EButtonOption::PRESS , dice , { EButtonType::KEYBOARD,DIK_S } , std::bind(&CDice::Rot , std::ref(dice) , 0));

	CFighter& fighter = *new CFighter(*this);
	mFighter = &fighter;

	CSkyDome& skyDome = *new CSkyDome(*this);

	CComponent* buf = nullptr;
	if(fighter.GetComponent<CCameraComponent>(buf))
	{
		CCameraComponent& camera = dynamic_cast<CCameraComponent&>(*buf);
		this->RequestSetCamera(camera);
	}
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

	CActor* buf;
	float distance;
	if(GetActor<CDice>(buf))
	{
		XMFLOAT3 vec;
		LCMath::CalcFloat3FromStartToGoal(mFighter->Transform.Location , buf->Transform.Location , vec);
		LCMath::CalcFloat3Length(vec , distance);
	}

	auto displayCount = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(10 , 10) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(200 , 200) , ImGuiCond_Once);

		ImGui::Begin(u8"フレームカウント");

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

	auto displayHitStatus = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(10 , 430) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(200 , 200) , ImGuiCond_Once);

		ImGui::Begin(u8"衝突判定");

		if(mFighter->isHit)ImGui::Text(u8"当たっている");
		else ImGui::Text(u8"当たっていない");

		ImGui::End();
	};

	auto displayDistance = [& , distance]
	{
		ImGui::SetNextWindowPos(ImVec2(220 , 10) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(200 , 200) , ImGuiCond_Once);

		ImGui::Begin(u8"距離");
		ImGui::Text(std::to_string(distance).c_str());

		ImGui::End();
	};

	AddImGuiDrawMethod(displayCount);
	AddImGuiDrawMethod(displayTime);
	AddImGuiDrawMethod(displayHitStatus);
	AddImGuiDrawMethod(displayDistance);
}