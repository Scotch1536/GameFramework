#include <string>
#include <random>

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
#include "CTest2D.h"

void CTestLevel::Init()
{

	/*CDice* subDice = nullptr;
	subDice = new CDice(*this);
	dice.Transform.AttachTransform(subDice->Transform);
	subDice->Transform.Location.y = -100.0f;
	subDice = new CDice(*this);
	dice.Transform.AttachTransform(subDice->Transform);
	subDice->Transform.Location.y = 100.0f;
	subDice = new CDice(*this);
	dice.Transform.AttachTransform(subDice->Transform);
	subDice->Transform.Location.x = -100.0f;
	subDice = new CDice(*this);
	dice.Transform.AttachTransform(subDice->Transform);
	subDice->Transform.Location.x = 100.0f;*/

	CFighter& fighter = *new CFighter(*this);
	mFighter = &fighter;
	mFighter->Transform.Location.z = 30.0f;

	CDice& dice = *new CDice(*this, mFighter->Transform.Location);
	dice.Transform.Location = { 0.f,0.f,500.f };
	mMainDice = &dice;

	CSkyDome& skyDome = *new CSkyDome(*this);

	CTest2D& test2D = *new CTest2D(*this);

	CComponent* buf = nullptr;
	if (fighter.GetComponent<CCameraComponent>(buf))
	{
		CCameraComponent& camera = dynamic_cast<CCameraComponent&>(*buf);
		this->RequestSetCamera(camera);
	}

	/*
	レベルから指定のアクターインスタンスのメソッドをインプットマネージャーにバインドすることは可能
	アクターからでもレベルからでもどちらでも可能だ
	*/
	//CInputManager::GetInstance().AddEvent("DiceDestroy" , EButtonOption::TRIGGER , *this , { EButtonType::KEYBOARD,DIK_Q } , std::bind(&CTestLevel::MainDiceDestroy , std::ref(*this)));
}

void CTestLevel::Tick()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	mCnt++;

	if (mCnt % 300 == 0)
	{
		int value = mt() % 3 + 1;
		if (value == 1)
		{
			CDice* subDice = nullptr;
			subDice = new CDice(*this, mFighter->Transform.Location);
			subDice->Transform.Location.x = mFighter->Transform.Location.x + 100;
		}
		else if (value == 2)
		{
			CDice* subDice = nullptr;
			subDice = new CDice(*this, mFighter->Transform.Location);
			subDice->Transform.Location.y = mFighter->Transform.Location.y + 100;
		}
		else
		{
			CDice* subDice = nullptr;
			subDice = new CDice(*this, mFighter->Transform.Location);
			subDice->Transform.Location.z = mFighter->Transform.Location.z + 100;
		}
	}

	int64_t dt = CGameManager::GetInstance().GetDeltaTime();
	if (dt != 0)
	{
		mTime += static_cast<float>(dt / 1000.0f);
		//mTime = std::floorf(mTime * 100.0f) / 100.0f;
	}

	auto displayCount = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Once);

		ImGui::Begin(u8"ゲーム情報");

		ImGui::Text(u8"フレームカウント");
		ImGui::Text(std::to_string(mCnt).c_str());

		ImGui::Text("\n");
		ImGui::Text(u8"時間");

		std::string buf = std::to_string(mTime);
		ImGui::Text(std::to_string(mTime).c_str());

		ImGui::End();
	};

	auto displayTime = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(10, 220), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Once);

		ImGui::Begin(u8"マウス情報");

		ImGui::Text(u8"マウス座標(クライアント)");

		std::string directXPos = std::to_string(CInputManager::GetInstance().GetMousePosX()) + "," + std::to_string(CInputManager::GetInstance().GetMousePosY());
		POINT mousePos;
		GetCursorPos(&mousePos);
		std::string winPos = std::to_string(mousePos.x) + "," + std::to_string(mousePos.y);

		ImGui::Text(directXPos.c_str());

		ImGui::Text("\n");
		ImGui::Text(u8"マウス座標(ディスプレイ)");
		ImGui::Text(winPos.c_str());

		ImGui::End();
	};

	auto displayHitStatus = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(10, 430), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(150, 100), ImGuiCond_Once);

		ImGui::Begin(u8"戦闘機の衝突判定");

		if (mFighter->GetIsHit())ImGui::Text(u8"当たっている");
		else ImGui::Text(u8"当たっていない");
		ImGui::End();
	};

	float distance;
	XMFLOAT3 vec;
	LCMath::CalcFloat3FromStartToGoal(mFighter->Transform.Location, mMainDice->Transform.Location, vec);
	LCMath::CalcFloat3Length(vec, distance);

	XMFLOAT3 angle = mFighter->Transform.Rotation.GetAngle();
	std::string angleStr = std::to_string((int)angle.x) + ',' + std::to_string((int)angle.y) + ',' + std::to_string((int)angle.z);
	auto displayDistance = [&, distance, angleStr]
	{
		ImGui::SetNextWindowPos(ImVec2(220, 10), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Once);

		ImGui::Begin(u8"戦闘機情報");

		ImGui::Text(u8"目標との距離");
		ImGui::Text(std::to_string(distance).c_str());

		ImGui::Text("\n");
		ImGui::Text(u8"角度");
		ImGui::Text(angleStr.c_str());

		ImGui::End();
	};

	auto displayHowToPlay = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(10, 550), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(400, 150), ImGuiCond_Once);

		ImGui::Begin(u8"操作方法");

		ImGui::Text(u8"マウス操作:ポインターの移動\n");
		ImGui::Text(u8"マウス左クリック:弾の発射\n");
		ImGui::Text("\n");
		ImGui::Text(u8"ゲーム概要：戦闘機はポインターに向かって移動します\n");
		ImGui::Text(u8"これはゲームフレームワークのひな形です\n");

		ImGui::End();
	};

	AddImGuiDrawMethod(displayCount);
	AddImGuiDrawMethod(displayTime);
	AddImGuiDrawMethod(displayHitStatus);
	AddImGuiDrawMethod(displayDistance);
	AddImGuiDrawMethod(displayHowToPlay);
}

void CTestLevel::MainDiceDestroy()
{
	if (mMainDice != nullptr)
	{
		mMainDice->Destroy();
		mMainDice = nullptr;
	}
}