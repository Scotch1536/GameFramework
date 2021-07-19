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
	���x������w��̃A�N�^�[�C���X�^���X�̃��\�b�h���C���v�b�g�}�l�[�W���[�Ƀo�C���h���邱�Ƃ͉\
	�A�N�^�[����ł����x������ł��ǂ���ł��\��
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

		ImGui::Begin(u8"�Q�[�����");

		ImGui::Text(u8"�t���[���J�E���g");
		ImGui::Text(std::to_string(mCnt).c_str());

		ImGui::Text("\n");
		ImGui::Text(u8"����");

		std::string buf = std::to_string(mTime);
		ImGui::Text(std::to_string(mTime).c_str());

		ImGui::End();
	};

	auto displayTime = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(10, 220), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(200, 200), ImGuiCond_Once);

		ImGui::Begin(u8"�}�E�X���");

		ImGui::Text(u8"�}�E�X���W(�N���C�A���g)");

		std::string directXPos = std::to_string(CInputManager::GetInstance().GetMousePosX()) + "," + std::to_string(CInputManager::GetInstance().GetMousePosY());
		POINT mousePos;
		GetCursorPos(&mousePos);
		std::string winPos = std::to_string(mousePos.x) + "," + std::to_string(mousePos.y);

		ImGui::Text(directXPos.c_str());

		ImGui::Text("\n");
		ImGui::Text(u8"�}�E�X���W(�f�B�X�v���C)");
		ImGui::Text(winPos.c_str());

		ImGui::End();
	};

	auto displayHitStatus = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(10, 430), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(150, 100), ImGuiCond_Once);

		ImGui::Begin(u8"�퓬�@�̏Փ˔���");

		if (mFighter->GetIsHit())ImGui::Text(u8"�������Ă���");
		else ImGui::Text(u8"�������Ă��Ȃ�");
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

		ImGui::Begin(u8"�퓬�@���");

		ImGui::Text(u8"�ڕW�Ƃ̋���");
		ImGui::Text(std::to_string(distance).c_str());

		ImGui::Text("\n");
		ImGui::Text(u8"�p�x");
		ImGui::Text(angleStr.c_str());

		ImGui::End();
	};

	auto displayHowToPlay = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(10, 550), ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(400, 150), ImGuiCond_Once);

		ImGui::Begin(u8"������@");

		ImGui::Text(u8"�}�E�X����:�|�C���^�[�̈ړ�\n");
		ImGui::Text(u8"�}�E�X���N���b�N:�e�̔���\n");
		ImGui::Text("\n");
		ImGui::Text(u8"�Q�[���T�v�F�퓬�@�̓|�C���^�[�Ɍ������Ĉړ����܂�\n");
		ImGui::Text(u8"����̓Q�[���t���[�����[�N�̂ЂȌ`�ł�\n");

		ImGui::End();
	};

	if (mFighter->GetIsHit())
	{
		mOwnerInterface->LoadLevel(*new CTestLevel(*mOwnerInterface));
	}

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