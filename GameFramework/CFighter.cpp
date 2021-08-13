#include "CFighter.h"

#include "GameFramework/Level/CLevel.h"
#include "GameFramework/DebugTools/imgui/myimgui.h"

#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Components/CAABBColliderComponent.h"
#include "GameFramework/Components/CLightComponent.h"
#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CSpringArmComponent.h"

#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CSoundManager.h"
#include "GameFramework/Managers/CGameManager.h"
#include "GameFramework/Game/CApplication.h"

#include "CTestLevel.h"
#include "CBullet.h"

CFighter::CFighter(ILevel& owner):CActor(owner) , mPointer(*new CPointer(owner , *this))
{
	Transform.AttachTransform(mPointer.Transform);
	mPointer.Transform.Location.y = 4.0f;
	mPointer.Transform.Location.z = 100.0f;

	//�^�O�ǉ�
	AddTag("Fighter");

	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/shot.wav" , 0.05f , false , "SHOT");

	/*
	�����d�v��
	�R���|�[�l���g�̓R���X�g���N�^�̈���owner�ɂ��ꂽ�A�N�^�[�Ɏ����Œǉ������
	���̍ی����q�[�v�̈��(new��)�쐬���邱��
	*/
	CStaticMeshComponent& mesh = *new CStaticMeshComponent(*this , Transform ,
		CModelDataManager::GetInstance().GetModel("Assets/Models/Fighter/F-15E.fbx" , "Assets/Models/Fighter/Textures/") ,
		"Shader/vs.hlsl" , "Shader/ps.hlsl");

	mesh.Transform.Rotation.SetAngle({ -90.0f ,0.0f,180.0f });

	CLightComponent& light = *new CLightComponent(*this);

	CCameraComponent& camera = *new CCameraComponent(*this);

	XMFLOAT3 fv = Transform.GetForwardVector();
	XMFLOAT3 loc = Transform.Location;
	XMFLOAT3 cameraLoc = Transform.Location;
	cameraLoc.x += fv.x*-20.0f;
	cameraLoc.y += fv.y*-20.0f+2.0f;
	cameraLoc.z += fv.z*-100.0f;

	camera.SetProjection(10.f , 10000.f , XM_PI / 4.f , CApplication::CLIENT_WIDTH , CApplication::CLIENT_HEIGHT);
	camera.SetView(cameraLoc , loc , { 0.f,1.f,0.f });

	CSpringArmComponent& spr = *new CSpringArmComponent(*this , Transform , camera);
	spr.SetLerpTime(0.5f);

	light.SetEyePos(camera.GetEye());
	light.SetLightPos(XMFLOAT4(1.f , 1.f , -1.f , 0.f));
	light.SetAmbient(XMFLOAT4(0.1f , 0.1f , 0.1f , 0.0f));

	CSphereColliderComponent& collider = *new CSphereColliderComponent(*this , mesh.GetModel() , mesh.Transform);

	//Transform.RequestDebugLine();

	/*
	�����d�v��
	�{�^���̓��͂ŌĂт����������\�b�h�͂��̂悤�ɃC���v�b�g�}�l�[�W���[�ɒǉ��ł���
	���ɂ��ǉ����@������̂ŃC���v�b�g�}�l�[�W���[�̃w�b�_�[���m�F���邱�Ƃ𐄏�
	*/
	CInputManager::GetInstance().AddEvent("Shot" , EButtonOption::PRESS , *this , { EButtonType::MOUSE,EMouseButtonType::L_BUTTON } , std::bind(&CFighter::Shot , std::ref(*this)));
	CInputManager::GetInstance().AddEvent("Rot-Y" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_A } , std::bind(&CFighter::Rot , std::ref(*this) , 0));
	CInputManager::GetInstance().AddEvent("Rot+Y" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_D } , std::bind(&CFighter::Rot , std::ref(*this) , 1));
	CInputManager::GetInstance().AddEvent("Rot-X" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_W } , std::bind(&CFighter::Rot , std::ref(*this) , 2));
	CInputManager::GetInstance().AddEvent("Rot+X" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_S } , std::bind(&CFighter::Rot , std::ref(*this) , 3));
	CInputManager::GetInstance().AddEvent("Reset" , EButtonOption::RELEASE , *this , { EButtonType::MOUSE,EMouseButtonType::L_BUTTON } , std::bind(&CFighter::ShotReset , std::ref(*this)));
}

void CFighter::Shot()
{
	if(mShotCnt % 5 != 0)
	{
		mShotCnt++;
		return;
	}
	mShotCnt++;

	XMFLOAT3 loc = Transform.GetWorldLocation();
	XMFLOAT3 fv = Transform.GetForwardVector();
	XMFLOAT3 dire;

	loc.x += fv.x * 10.0f;
	loc.y += fv.y * 10.0f + 2.0f;
	loc.z += fv.z * 10.0f;

	LCMath::CalcFloat3FromStartToGoal(loc , mPointer.Transform.GetWorldLocation() , dire);
	LCMath::CalcFloat3Normalize(dire , dire);

	new CBullet(mOwnerInterface , loc , dire , 60 * 3);

	CSoundManager::GetInstance().PlaySound("SHOT");
}

void CFighter::ShotReset()
{
	mShotCnt = 0;
}

void CFighter::Move()
{
	XMFLOAT3 fv = Transform.GetForwardVector();

	Transform.Location.x += fv.x * 1;
	Transform.Location.y += fv.y * 1;
	Transform.Location.z += fv.z * 1;
}

void CFighter::Rot(int dire)
{
	if(dire == 0)Transform.Rotation.AddAngle({ 0.0f,-1.0f,0.0f });
	else if(dire == 1)Transform.Rotation.AddAngle({ 0.0f,1.0f,0.0f });
	else if(dire == 2)Transform.Rotation.AddAngle({ -1.0f,0.0f,0.0f });
	else if(dire == 3)Transform.Rotation.AddAngle({ 1.0f,0.0f,0.0f });
}

void CFighter::Tick()
{
	
	Move();

	if(mTargetRot != nullptr)
	{
		bool isEnd = false;
		XMFLOAT4 result;

		mAlpha += mIncrementAlpha;
		if(mAlpha > 1.0f)
		{
			mAlpha = 1.0f;
			isEnd = true;
		}

		LCMath::Lerp(mStartRot , *mTargetRot , mAlpha , result);
		Transform.Rotation.SetQuaternion(result);

		if(isEnd)
		{
			mTargetRot.reset();
		}
	}

	XMFLOAT3 loc = Transform.GetWorldLocation();
	XMFLOAT3 fv = Transform.GetForwardVector();
	XMFLOAT3 dire;

	LCMath::CalcFloat3FromStartToGoal(loc , mPointer.Transform.GetWorldLocation() , dire);
	LCMath::CalcFloat3Normalize(dire , dire);

	auto displayPointer = [& , fv , dire]
	{
		ImGui::SetNextWindowPos(ImVec2(CApplication::CLIENT_WIDTH - 210 , 220) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(200 , 200) , ImGuiCond_Once);

		ImGui::Begin(u8"�퓬�@�ƃ|�C���^�[�Ƃ̃x�N�g�����");

		std::string forvec = u8"�퓬�@�̑O���x�N�g��\n" + std::to_string(fv.x) + "," + std::to_string(fv.y) + "," + std::to_string(fv.z);
		std::string direvec = u8"�퓬�@�ƃ|�C���^�[�Ƃ̌����x�N�g��\n" + std::to_string(dire.x) + "," + std::to_string(dire.y) + "," + std::to_string(dire.z);
		ImGui::Text(forvec.c_str());
		ImGui::Text(direvec.c_str());

		ImGui::End();
	};
	mOwnerInterface.AddImGuiDrawMethod(displayPointer);
}

void CFighter::EventAtBeginCollide(CActor& collideActor)
{
	/*if(collideActor.HasTag("Dice"))
	{
		mOwnerInterface.RequestLoadLevel(*new CTestLevel(CGameManager::GetInstance().GetGameInterface()));
		mIsHit = true;
	}*/
}

void CFighter::EventAtEndCollide(CActor& collideActor)
{
	if(collideActor.HasTag("Dice"))
	{
		mIsHit = false;
	}
}