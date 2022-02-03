//!
//! @file
//! @brief ���C���Q�[�����x���̃\�[�X�t�@�C��
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
	//�t�F�[�h�A�N�^�[�쐬
	new CFeedActor(*this , nullptr , CFeedActor::EOption::FEEDIN);

	CComponent* buf;

	//�퓬�@�쐬&������
	CFighter& fighter = *new CFighter(*this);
	fighter.Transform.Location.z = -500.0f;

	//�X�J�C�h�[���쐬
	CSkyDome& skyDome = *new CSkyDome(*this);

	//�퓬�@�ɃX�J�C�h�[�����A�^�b�`
	fighter.Transform.AttachTransform(skyDome.Transform);

	//�X�J�C�h�[���̃A�^�b�`�I�v�V���������P�[�V�����݂̂ɐݒ�
	skyDome.Transform.SetAttachOption(CTransform::EAttachOption::LOCATION_ONLY);

	XMFLOAT3 min , max;
	min = max = { 0.0f,0.0f,0.0f };

	skyDome.GetComponent<CStaticMeshComponent>(buf);
	CStaticMeshComponent& skyDomeMesh = dynamic_cast<CStaticMeshComponent&>(*buf);

	//�X�J�C�h�[�����b�V������ŏ��ő�l�����߂�
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

	//���[���h���ɕϊ�
	min.x *= (skyDomeMesh.Transform.Scale.x / 2.0f);
	min.y *= (skyDomeMesh.Transform.Scale.y / 2.0f);
	min.z *= (skyDomeMesh.Transform.Scale.z / 2.0f);
	max.x *= (skyDomeMesh.Transform.Scale.x / 2.0f);
	max.y *= (skyDomeMesh.Transform.Scale.y / 2.0f);
	max.z *= (skyDomeMesh.Transform.Scale.z / 2.0f);

	//�A�N�^�[�W�F�l���[�^�쐬
	new CActorGenerator(*this , [&] { return new CAttachObject(*this); } , min , max , 15.0f);

	fighter.GetComponent<CCameraComponent>(buf);
	SetRenderCamera(*dynamic_cast<CCameraComponent*>(buf));			//�`��J�����Z�b�g

	//���C�g�̃Z�b�g
	CLightManager::GetInstance().SetDirectionLight({ 1.0f,1.0f,-1.0f });
	CLightManager::GetInstance().SetAmbientLight({ 0.1f,0.1f,0.1f });
}

void CMainGameLevel::Tick()
{
	//�������ԍX�V
	mTime -= CGameManager::GetInstance().GetDeltaTime();

	//�I�����Ă�����
	if(mTime <= 0.0f && !mIsEnd)
	{
		mIsEnd = true;

		std::string scoreStr = "Score:" + std::to_string(mScore);
		MessageBox(nullptr , scoreStr.c_str() , "GameOver!" , MB_OK);

		//�^�C�g�����x���ɑJ��
		new CTitle(mOwnerInterface , true);
	}

	//GUI�쐬����
	auto displayHowTo = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(10 , 10) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(450 , 150) , ImGuiCond_Once);

		ImGui::Begin(u8"�V�ѕ�");
		ImGui::Text(u8"������@\nWASD:�퓬�@�̕����ύX\n���N���b�N�i�������j:�X�s�[�h�A�b�v\n�E�N���b�N�i�������j:�X�s�[�h�_�E��\n");
		ImGui::Text("\n");
		ImGui::Text(u8"�V�ѕ�:�ł��邾�������̃I�u�W�F�N�g�𓖂����Ă������悤�I");

		ImGui::End();
	};
	auto displayScore = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(CApplication::CLIENT_WIDTH - 110 , 10) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(100 , 50) , ImGuiCond_Once);

		ImGui::Begin(u8"�X�R�A");
		ImGui::Text(std::to_string(mScore).c_str());

		ImGui::End();
	};
	auto displayTime = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(CApplication::CLIENT_WIDTH - 110 , 70) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(100 , 50) , ImGuiCond_Once);

		ImGui::Begin(u8"��������");
		ImGui::Text(std::to_string(static_cast<int>(mTime)).c_str());

		ImGui::End();
	};
	AddImGuiDrawEvent(displayHowTo);
	AddImGuiDrawEvent(displayScore);
	AddImGuiDrawEvent(displayTime);
}

void CMainGameLevel::Notice(CActor& actor)
{
	//�A�^�b�`�I�u�W�F�N�g����̒ʒm�Ȃ�
	if(actor.HasTag("AttachObject"))
	{
		mScore += 1;
	}
}