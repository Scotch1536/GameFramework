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
#include "CTestPlane.h"

void CTestLevel::Init()
{
	CTestPlane& plane = *new CTestPlane(*this);
	plane.Transform.Location.z = 100.0f;
	//plane.Transform.Scale = { 50.0f,50.0f,0.0f };

	CDice& dice = *new CDice(*this);
	mDice = &dice;

	dice.Transform.Location = { 50.f,0.f,100.f };

	CFighter& fighter = *new CFighter(*this);
	//fighter.Transform.Rotation.SetAngle({ 0.0f,30.0f,0.0f });
	mFighter = &fighter;

	CSkyDome& skyDome = *new CSkyDome(*this);

	CComponent* buf = nullptr;
	if(fighter.GetComponent<CCameraComponent>(buf))
	{
		CCameraComponent& camera = dynamic_cast<CCameraComponent&>(*buf);
		this->RequestSetCamera(camera);
	}

	/*
	レベルから指定のアクターインスタンスのメソッドをインプットマネージャーにバインドすることは可能
	アクターからでもレベルからでもどちらでも可能だ
	*/
	CInputManager::GetInstance().AddEvent("ChangeDire" , EButtonOption::TRIGGER , *this , { EButtonType::KEYBOARD,DIK_Q } , std::bind(&CTestLevel::ChangeFighterAngleToDirectionDice , std::ref(*this)));
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

	XMFLOAT3 angle = mFighter->Transform.Rotation.GetAngle();
	std::string angleStr = std::to_string((int)angle.x) + ',' + std::to_string((int)angle.y) + ',' + std::to_string((int)angle.z);
	auto displayDistance = [& , distance , angleStr]
	{
		ImGui::SetNextWindowPos(ImVec2(220 , 10) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(200 , 200) , ImGuiCond_Once);

		ImGui::Begin(u8"戦闘機情報");

		ImGui::Text(u8"目標との距離");
		ImGui::Text(std::to_string(distance).c_str());

		ImGui::Text("\n");
		ImGui::Text(u8"角度");
		ImGui::Text(angleStr.c_str());

		ImGui::End();
	};

	AddImGuiDrawMethod(displayCount);
	AddImGuiDrawMethod(displayTime);
	AddImGuiDrawMethod(displayHitStatus);
	AddImGuiDrawMethod(displayDistance);
}

void CTestLevel::ChangeFighterAngleToDirectionDice()
{
	XMFLOAT4 qua;
	if(mFighter->Transform.Rotation.CalcQuaternionToLocation(mDice->Transform.Location , qua))
	{
		mFighter->Transform.Rotation.SetQuaternion(qua);
	}
}