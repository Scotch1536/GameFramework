//!
//! @file
//! @brief メインゲームレベルのソースファイル
//!

#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CParticleGeneratorComponent.h"
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
	//フェードアクター作成
	new CFeedActor(*this , nullptr , CFeedActor::EOption::FEEDIN);

	CComponent* buf;

	//戦闘機作成&初期化
	CFighter& fighter = *new CFighter(*this);
	fighter.Transform.Location.z = -500.0f;

	//スカイドーム作成
	CSkyDome& skyDome = *new CSkyDome(*this);

	//戦闘機にスカイドームをアタッチ
	fighter.Transform.AttachTransform(skyDome.Transform);

	//スカイドームのアタッチオプションをロケーションのみに設定
	skyDome.Transform.SetAttachOption(CTransform::EAttachOption::LOCATION_ONLY);

	XMFLOAT3 min , max;
	min = max = { 0.0f,0.0f,0.0f };

	skyDome.GetComponent<CStaticMeshComponent>(buf);
	CStaticMeshComponent& skyDomeMesh = dynamic_cast<CStaticMeshComponent&>(*buf);

	//スカイドームメッシュから最小最大値を求める
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

	//ワールド情報に変換
	min.x *= (skyDomeMesh.Transform.Scale.x / 2.0f);
	min.y *= (skyDomeMesh.Transform.Scale.y / 2.0f);
	min.z *= (skyDomeMesh.Transform.Scale.z / 2.0f);
	max.x *= (skyDomeMesh.Transform.Scale.x / 2.0f);
	max.y *= (skyDomeMesh.Transform.Scale.y / 2.0f);
	max.z *= (skyDomeMesh.Transform.Scale.z / 2.0f);

	//アクタージェネレータ作成
	new CActorGenerator(*this , [&] { return new CAttachObject(*this); } , min , max , 15.0f);

	fighter.GetComponent<CCameraComponent>(buf);
	SetRenderCamera(*dynamic_cast<CCameraComponent*>(buf));			//描画カメラセット

	//ライトのセット
	CLightManager::GetInstance().SetDirectionLight({ 1.0f,1.0f,-1.0f });
	CLightManager::GetInstance().SetAmbientLight({ 0.1f,0.1f,0.1f });
}

void CMainGameLevel::Tick()
{
	//制限時間更新
	mTime -= CGameManager::GetInstance().GetDeltaTime();

	//終了していたら
	if(mTime <= 0.0f && !mIsEnd)
	{
		mIsEnd = true;

		std::string scoreStr = "Score:" + std::to_string(mScore);
		MessageBox(nullptr , scoreStr.c_str() , "GameOver!" , MB_OK);

		//タイトルレベルに遷移
		new CTitle(mOwnerInterface , true);
	}

	//GUI作成処理
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
	AddImGuiDrawEvent(displayHowTo);
	AddImGuiDrawEvent(displayScore);
	AddImGuiDrawEvent(displayTime);
}

void CMainGameLevel::Notice(CActor& actor)
{
	//アタッチオブジェクトからの通知なら
	if(actor.HasTag("AttachObject"))
	{
		mScore += 1;
	}
}