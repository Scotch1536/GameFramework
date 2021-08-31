#include "GameFramework/Level/CLevel.h"
#include "GameFramework/ExternalTools/imgui/myimgui.h"

#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Components/CLightComponent.h"
#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CSpringArmComponent.h"

#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CSoundManager.h"
#include "GameFramework/Managers/CGameManager.h"
#include "GameFramework/Game/CApplication.h"

#include "CBullet.h"
#include "CFighter.h"

CFighter::CFighter(ILevel& owner):CActor(owner) , mPointer(*new CPointer(owner , *this)) ,
mSpeedLimitMin(mSpeed / 2.0f) , mSpeedLimitMax(mSpeed*2.0f)
{
	Transform.AttachTransform(mPointer.Transform);
	mPointer.Transform.Location.y = 4.0f;
	mPointer.Transform.Location.z = 100.0f;

	//タグ追加
	AddTag("Fighter");

	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/shot.wav" , 0.05f , false , "SHOT");

	/*
	★超重要★
	コンポーネントはコンストラクタの引数ownerにいれたアクターに自動で追加される
	その際原則ヒープ領域に(newで)作成すること
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
	cameraLoc.y += fv.y*-20.0f + 2.0f;
	cameraLoc.z += fv.z*-20.0f;

	camera.SetProjection(10.f , 10000.f , XM_PI / 4.f , CApplication::CLIENT_WIDTH , CApplication::CLIENT_HEIGHT);
	camera.SetView(cameraLoc , loc , { 0.f,1.f,0.f });

	CSpringArmComponent& spr = *new CSpringArmComponent(*this , Transform , camera);
	spr.SetLerpTime(0.5f);

	light.SetEyePos(camera.GetEye());
	light.SetLightPos(XMFLOAT4(1.f , 1.f , -1.f , 0.f));
	light.SetAmbient(XMFLOAT4(0.1f , 0.1f , 0.1f , 0.0f));

	CSphereColliderComponent& collider = *new CSphereColliderComponent(*this , mesh.GetModel() , Transform);
	collider.Transform.Scale = { 0.8f,0.8f,0.8f };
	collider.Transform.Location.y += 2.0f;
	collider.Transform.Location.z -= 2.0f;

	Transform.RequestDebugLine();

	/*
	★超重要★
	ボタンの入力で呼びだしたいメソッドはこのようにインプットマネージャーに追加できる
	他にも追加方法があるのでインプットマネージャーのヘッダーを確認することを推奨
	*/
	//CInputManager::GetInstance().AddEvent("Shot" , EButtonOption::PRESS , *this , { EButtonType::MOUSE,EMouseButtonType::L_BUTTON } , std::bind(&CFighter::Shot , std::ref(*this)));
	CInputManager::GetInstance().AddEvent("Rot-Y" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_A } , std::bind(&CFighter::Rot , std::ref(*this) , 0));
	CInputManager::GetInstance().AddEvent("Rot+Y" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_D } , std::bind(&CFighter::Rot , std::ref(*this) , 1));
	CInputManager::GetInstance().AddEvent("Rot-X" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_W } , std::bind(&CFighter::Rot , std::ref(*this) , 2));
	CInputManager::GetInstance().AddEvent("Rot+X" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_S } , std::bind(&CFighter::Rot , std::ref(*this) , 3));
	CInputManager::GetInstance().AddEvent("SpeedUP" , EButtonOption::PRESS , *this , { EButtonType::MOUSE,EMouseButtonType::L_BUTTON } , std::bind(&CFighter::SpeedChange , std::ref(*this) , 0));
	CInputManager::GetInstance().AddEvent("SpeedDPWN" , EButtonOption::PRESS , *this , { EButtonType::MOUSE,EMouseButtonType::R_BUTTON } , std::bind(&CFighter::SpeedChange , std::ref(*this) , 1));
	//CInputManager::GetInstance().AddEvent("Reset" , EButtonOption::RELEASE , *this , { EButtonType::MOUSE,EMouseButtonType::L_BUTTON } , std::bind(&CFighter::ShotReset , std::ref(*this)));
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
	float dt = CGameManager::GetInstance().GetDeltaTime();

	Transform.Location.x += fv.x * (mSpeed*dt);
	Transform.Location.y += fv.y * (mSpeed*dt);
	Transform.Location.z += fv.z * (mSpeed*dt);
}

void CFighter::Rot(int dire)
{
	if(dire == 0)Transform.Rotation.AddAngle({ 0.0f,-1.0f,0.0f });
	else if(dire == 1)Transform.Rotation.AddAngle({ 0.0f,1.0f,0.0f });
	else if(dire == 2)Transform.Rotation.AddAngle({ -1.0f,0.0f,0.0f });
	else if(dire == 3)Transform.Rotation.AddAngle({ 1.0f,0.0f,0.0f });
}

void CFighter::SpeedChange(int type)
{
	if(type == 0)
	{
		if(mSpeed < mSpeedLimitMax)mSpeed += 0.5f;
	}
	else if(type == 1)
	{
		if(mSpeed > mSpeedLimitMin)mSpeed -= 0.5f;
	}
}

void CFighter::Tick()
{
	Move();

	auto displayFighterInfo = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(10 , CApplication::CLIENT_HEIGHT - 110) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(200 , 100) , ImGuiCond_Once);

		ImGui::Begin(u8"戦闘機情報");

		std::string speedStr = u8"スピード:" + std::to_string(mSpeed);
		ImGui::Text(speedStr.c_str());

		ImGui::End();
	};
	mOwnerInterface.AddImGuiDrawFunction(displayFighterInfo);
}
