#include "CTestCharacter.h"
#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CLightComponent.h"
#include "GameFramework/Components/CSpringArmComponent.h"
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

	CSpringArmComponent* spr = new CSpringArmComponent(*this , Transform , *camera , ESyncMode::LOCATION_ONLY_SYNC);

	light->SetEyePos(camera->GetEye());
	light->SetLightPos(XMFLOAT4(1.f , 1.f , -1.f , 0.f));
	light->SetAmbient(XMFLOAT4(0.f , 0.f , 0.f , 0.f));

	CInputManager::GetInstance().AddAction("Move" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_C } , std::bind(&CTestCharacter::Move , std::ref(*this)));
	CInputManager::GetInstance().AddAction("XP" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_S } , std::bind(&CTestCharacter::Rot , std::ref(*this) , 0));
	CInputManager::GetInstance().AddAction("XM" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_D } , std::bind(&CTestCharacter::Rot , std::ref(*this) , 1));
	CInputManager::GetInstance().AddAction("YP" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_F } , std::bind(&CTestCharacter::Rot , std::ref(*this) , 2));
	CInputManager::GetInstance().AddAction("YM" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_G } , std::bind(&CTestCharacter::Rot , std::ref(*this) , 3));
	CInputManager::GetInstance().AddAction("ZP" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_H } , std::bind(&CTestCharacter::Rot , std::ref(*this) , 4));
	CInputManager::GetInstance().AddAction("ZM" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_J } , std::bind(&CTestCharacter::Rot , std::ref(*this) , 5));
	CInputManager::GetInstance().AddAction("XPM" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_K } , std::bind(&CTestCharacter::Rot , std::ref(*this) , 6));
	CInputManager::GetInstance().AddAction("Destroy" , EButtonOption::TRIGGER , *this , { EButtonType::KEYBOARD,DIK_L } , std::bind(&CActor::Destroy , std::ref(*this)));
}

void CTestCharacter::Move()
{
	Transform.Location.z--;
}

void CTestCharacter::Rot(int dire)
{
	switch(dire)
	{
	case 0:
		Transform.Rotation.Angle.x++;
		return;
	case 1:
		Transform.Rotation.Angle.x--;
		return;
	case 2:
		Transform.Rotation.Angle.y++;
		return;
	case 3:
		Transform.Rotation.Angle.y--;
		return;
	case 4:
		Transform.Rotation.Angle.z++;
		return;
	case 5:
		Transform.Rotation.Angle.z--;
		return;
	case 6:
		Transform.Location.x++;
		return;
	default:
		break;
	}
}