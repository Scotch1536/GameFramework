#include "CTestCharacter.h"
#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CLightComponent.h"
#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Game/Application.h"

CTestCharacter::CTestCharacter(ILevel& owner):CActor(owner)
{
	CStaticMeshComponent& staticMesh = *new CStaticMeshComponent(*this , CModelDataManager::GetInstance().GetModel("Assets/dice/Playerbox.x" , "Assets/dice/") ,
		"Shader/vs.hlsl" , "Shader/ps.hlsl");

	CLightComponent* light = new CLightComponent(*this);

	CCameraComponent* camera = new CCameraComponent(*this);
	camera->SetProjection(10.f , 10000.f , XM_PI / 4.f , Application::CLIENT_WIDTH , Application::CLIENT_HEIGHT);
	camera->SetView({ 0.f,0.f,-100.f } , { 0.f,0.f,0.f } , { 0.f,1.f,0.f });

	light->SetEyePos(camera->GetEye());
	light->SetLightPos(XMFLOAT4(1.f , 1.f , -1.f , 0.f));
	light->SetAmbient(XMFLOAT4(0.f , 0.f , 0.f , 0.f));

	CInputManager::GetInstance().AddAction("Move" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_C } , std::bind(&CTestCharacter::Move , std::ref(*this)));
}

void CTestCharacter::Move()
{
	Transform.Location.z--;
}