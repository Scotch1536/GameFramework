#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Actor/CActorGenerator.h"
#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Actor/CFeedActor.h"
#include "GameFramework/ExternalTools/imgui/myimgui.h"
#include "GameFramework/Game/CApplication.h"
#include "GameFramework/Managers/CGameManager.h"
#include "GameFramework/Managers/CLightManager.h"

#include "CFighter.h"
#include "CSkyDome.h"
#include "CAttachObject.h"

#include "CTitle.h"
#include "CMainGameLevel.h"

void CMainGameLevel::Init()
{
	new CFeedActor(*this , nullptr , CFeedActor::EOption::FEEDIN);

	CComponent* buf;

	CFighter& fighter = *new CFighter(*this);
	fighter.Transform.Location.z = -500.0f;

	CSkyDome& skyDome = *new CSkyDome(*this);
	fighter.Transform.AttachTransform(skyDome.Transform);
	skyDome.Transform.SetOption(CTransform::EAttachOption::LOCATION_ONLY);
	skyDome.GetComponent<CStaticMeshComponent>(buf);
	XMFLOAT3 min , max;
	min = max = { 0.0f,0.0f,0.0f };
	CStaticMeshComponent& skyDomeMesh = dynamic_cast<CStaticMeshComponent&>(*buf);

	for(auto& mesh : skyDomeMesh.GetModel().GetMeshes())
	{
		for(auto& vertex : mesh.Vertices)
		{
			if(min.x > vertex.Pos.x)min.x = vertex.Pos.x;
			else if(max.x < vertex.Pos.x)max.x = vertex.Pos.x;

			if(min.y > vertex.Pos.y)min.y = vertex.Pos.y;
			else if(max.y < vertex.Pos.y)max.y = vertex.Pos.y;

			if(min.z > vertex.Pos.z)min.z = vertex.Pos.z;
			else if(max.z < vertex.Pos.z)max.z = vertex.Pos.z;
		}
	}

	min.x *= (skyDomeMesh.Transform.Scale.x / 2.0f);
	min.y *= (skyDomeMesh.Transform.Scale.y / 2.0f);
	min.z *= (skyDomeMesh.Transform.Scale.z / 2.0f);
	max.x *= (skyDomeMesh.Transform.Scale.x / 2.0f);
	max.y *= (skyDomeMesh.Transform.Scale.y / 2.0f);
	max.z *= (skyDomeMesh.Transform.Scale.z / 2.0f);

	new CActorGenerator(*this , [&] { return new CAttachObject(*this); } , min , max , 15.0f);

	fighter.GetComponent<CCameraComponent>(buf);
	RequestSetCamera(*dynamic_cast<CCameraComponent*>(buf));

	CLightManager::GetInstance().SetDirectionLight({ 1.0f,1.0f,-1.0f });
	CLightManager::GetInstance().SetAmbientLight({ 0.1f,0.1f,0.1f });
}

void CMainGameLevel::Tick()
{
	mTime -= CGameManager::GetInstance().GetDeltaTime();

	if(mTime <= 0.0f && !mIsEnd)
	{
		mIsEnd = true;

		std::string scoreStr = "Score:" + std::to_string(mScore);
		MessageBox(nullptr , scoreStr.c_str() , "GameOver!" , MB_OK);
		new CTitle(mOwnerInterface , true);
	}

	auto displayHowTo = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(10 , 10) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(450 , 150) , ImGuiCond_Once);

		ImGui::Begin(u8"遊び方");
		ImGui::Text(u8"操作方法\nWASD:戦闘機の方向変更\n左クリック（長押し）:スピードアップ\n右クリック（長押し）:スピードダウン\n");
		ImGui::Text("\n");
		ImGui::Text(u8"遊び方:できるだけ多くのオブジェクトを当たってくっつけよう！");

		ImGui::End();
	};
	auto displayScore = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(CApplication::CLIENT_WIDTH - 110 , 10) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(100 , 50) , ImGuiCond_Once);

		ImGui::Begin(u8"スコア");
		ImGui::Text(std::to_string(mScore).c_str());

		ImGui::End();
	};
	auto displayTime = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(CApplication::CLIENT_WIDTH - 110 , 70) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(100 , 50) , ImGuiCond_Once);

		ImGui::Begin(u8"制限時間");
		ImGui::Text(std::to_string(static_cast<int>(mTime)).c_str());

		ImGui::End();
	};
	AddImGuiDrawFunction(displayHowTo);
	AddImGuiDrawFunction(displayScore);
	AddImGuiDrawFunction(displayTime);
}

void CMainGameLevel::Notice(CActor& actor)
{
	if(actor.HasTag("AttachObject"))
	{
		mScore += 1;
	}
}