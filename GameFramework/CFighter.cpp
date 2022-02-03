//!
//! @file
//! @brief 戦闘機アクターのソースファイル
//!

#include "GameFramework/Level/CLevel.h"
#include "GameFramework/ExternalTools/imgui/myimgui.h"

#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CSphereMeshComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CSpringArmComponent.h"
#include "GameFramework/Components/CParticleGeneratorComponent.h"

#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CSoundManager.h"
#include "GameFramework/Managers/CGameManager.h"
#include "GameFramework/Game/CApplication.h"

#include "CFighter.h"

CFighter::CFighter(ILevel& owner):CActor(owner) , mPointer(*new CPointer(owner , *this)) ,
mSpeedLimitMin(mSpeed / 2.0f) , mSpeedLimitMax(mSpeed*2.0f)
{
	//ポインタを自身にアタッチ
	Transform.AttachTransform(mPointer.Transform);
	mPointer.Transform.Location.y = 4.0f;
	mPointer.Transform.Location.z = 100.0f;

	//タグ追加
	AddTag("Fighter");

	//スタティックコンポーネント追加&初期化
	CStaticMeshComponent& mesh = *new CStaticMeshComponent(*this , Transform ,
		CModelDataManager::GetInstance().GetModel("Assets/Models/Fighter/F-15E.fbx" , "Assets/Models/Fighter/Textures/") ,
		"Shader/vs.hlsl" , "Shader/ps.hlsl");
	mesh.Transform.Rotation.SetAngle({ -90.0f ,0.0f,180.0f });

	//パーティクルボディ生成関数オブジェクト作成
	auto particleBody = [&](CActor& actor)
	{
		CSphereMeshComponent& sphere = *new CSphereMeshComponent(actor , actor.Transform , { 0.3f,0.3f,0.3f,0.8f });
		sphere.Transform.Scale = { 4.0f,4.0f,4.0f };
	};

	//パーティクル生成コンポーネント追加&初期化
	CParticleGeneratorComponent& particle = *new CParticleGeneratorComponent(*this , Transform , particleBody , 1.0f , 1.0f , 30.0f ,
		*new CParticleBaseGeneratorCone({ 0.0f,0.0f,-1.0f } , 60.0f) , 100000);
	particle.Transform.Location.z = -5.0f;

	//カメラコンポーネント追加
	CCameraComponent& camera = *new CCameraComponent(*this);

	//カメラコンポーネント初期化
	XMFLOAT3 fv = Transform.GetWorldForwardVector();
	XMFLOAT3 loc = Transform.Location;
	XMFLOAT3 cameraLoc = Transform.Location;
	cameraLoc.x += fv.x*-20.0f;
	cameraLoc.y += fv.y*-20.0f + 2.0f;
	cameraLoc.z += fv.z*-20.0f;

	camera.SetProjection(10.f , 10000.f , XM_PI / 4.f , CApplication::CLIENT_WIDTH , CApplication::CLIENT_HEIGHT);
	camera.SetView(cameraLoc , loc , { 0.f,1.f,0.f });

	//スプリングアームコンポーネント追加
	CSpringArmComponent& spr = *new CSpringArmComponent(*this , Transform , camera);
	spr.SetLerpTime(0.5f);		//線形補間時間のセット

	//スフィアコライダーコンポーネント追加&初期化
	CSphereColliderComponent& collider = *new CSphereColliderComponent(*this , mesh.GetModel() , Transform);
	collider.Transform.Scale = { 0.8f,0.8f,0.8f };
	collider.Transform.Location.y += 2.0f;
	collider.Transform.Location.z -= 2.0f;

	//デバッグラインリクエスト
	Transform.RequestDebugLine();

	//入力イベントの追加
	CInputManager::GetInstance().AddEvent("Rot-Y" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_A } , std::bind(&CFighter::Rot , std::ref(*this) , 0));
	CInputManager::GetInstance().AddEvent("Rot+Y" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_D } , std::bind(&CFighter::Rot , std::ref(*this) , 1));
	CInputManager::GetInstance().AddEvent("Rot-X" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_W } , std::bind(&CFighter::Rot , std::ref(*this) , 2));
	CInputManager::GetInstance().AddEvent("Rot+X" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_S } , std::bind(&CFighter::Rot , std::ref(*this) , 3));
	CInputManager::GetInstance().AddEvent("SpeedUP" , EButtonOption::PRESS , *this , { EButtonType::MOUSE,EMouseButtonType::L_BUTTON } , std::bind(&CFighter::SpeedChange , std::ref(*this) , 0));
	CInputManager::GetInstance().AddEvent("SpeedDOWN" , EButtonOption::PRESS , *this , { EButtonType::MOUSE,EMouseButtonType::R_BUTTON } , std::bind(&CFighter::SpeedChange , std::ref(*this) , 1));
}

void CFighter::Move()
{
	XMFLOAT3 fv = Transform.GetWorldForwardVector();
	float dt = CGameManager::GetInstance().GetDeltaTime();

	//ロケーション更新
	Transform.Location.x += fv.x * (mSpeed*dt);
	Transform.Location.y += fv.y * (mSpeed*dt);
	Transform.Location.z += fv.z * (mSpeed*dt);
}

void CFighter::Rot(int dire)
{
	if(dire == 0)Transform.Rotation.AddAngleWorld({ 0.0f,-1.0f,0.0f });
	else if(dire == 1)Transform.Rotation.AddAngleWorld({ 0.0f,1.0f,0.0f });
	else if(dire == 2)Transform.Rotation.AddAngleWorld({ -1.0f,0.0f,0.0f });
	else if(dire == 3)Transform.Rotation.AddAngleWorld({ 1.0f,0.0f,0.0f });
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
	//移動
	Move();

	//GUI作成
	auto displayFighterInfo = [&]
	{
		ImGui::SetNextWindowPos(ImVec2(10 , CApplication::CLIENT_HEIGHT - 60) , ImGuiCond_Once);
		ImGui::SetNextWindowSize(ImVec2(100 , 50) , ImGuiCond_Once);

		ImGui::Begin("Speed");

		std::string speedStr = std::to_string(static_cast<int>(mSpeed));
		ImGui::Text(speedStr.c_str());

		ImGui::End();
	};
	mOwnerInterface.AddImGuiDrawEvent(displayFighterInfo);
}
