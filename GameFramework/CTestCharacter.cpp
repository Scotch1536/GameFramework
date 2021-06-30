#include "CTestCharacter.h"
#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CLightComponent.h"
#include "GameFramework/Components/CSpringArmComponent.h"
#include "GameFramework/Components/CAABBComponent.h"
#include "GameFramework/Components/CSphereComponent.h"
#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Managers/CGameManager.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Game/CApplication.h"

CTestCharacter::CTestCharacter(ILevel& owner):CActor(owner)
{
	//Transform.Scale = { 2,2,2 };
	CStaticMeshComponent& staticMesh = *new CStaticMeshComponent(*this , CModelDataManager::GetInstance().GetModel("Assets/dice/Playerbox.x" , "Assets/dice/") ,
		"Shader/vs.hlsl" , "Shader/ps.hlsl");

	//staticMesh.Transform.Scale = { 2,2,2 };

	CLightComponent* light = new CLightComponent(*this);

	CCameraComponent* camera = new CCameraComponent(*this);

	camera->SetProjection(10.f , 10000.f , XM_PI / 4.f , CApplication::CLIENT_WIDTH , CApplication::CLIENT_HEIGHT);
	camera->SetView({ 0.f,0.f,-100.f } , Transform.Location , { 0.f,1.f,0.f });

	CSpringArmComponent* spr = new CSpringArmComponent(*this , Transform , *camera);
	spr->SetLerpTime(1.0f);

	light->SetEyePos(camera->GetEye());
	light->SetLightPos(XMFLOAT4(1.f , 1.f , -1.f , 0.f));
	light->SetAmbient(XMFLOAT4(0.1f , 0.1f , 0.1f , 0.0f));

	CAABBComponent* aabb = new CAABBComponent(*this , staticMesh.GetModel() , staticMesh.Transform);

	aabb->BindCollisionAction(std::bind(&CTestCharacter::CollisionAction , std::ref(*this) , std::placeholders::_1));

	CInputManager::GetInstance().AddAction("MoveM" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_W } , std::bind(&CTestCharacter::Move , std::ref(*this) , 0));
	CInputManager::GetInstance().AddAction("MoveP" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_S } , std::bind(&CTestCharacter::Move , std::ref(*this) , 1));
	CInputManager::GetInstance().AddAction("XP" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_R } , std::bind(&CTestCharacter::Rot , std::ref(*this) , 0));
	CInputManager::GetInstance().AddAction("XM" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_T } , std::bind(&CTestCharacter::Rot , std::ref(*this) , 1));
	CInputManager::GetInstance().AddAction("YP" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_F } , std::bind(&CTestCharacter::Rot , std::ref(*this) , 2));
	CInputManager::GetInstance().AddAction("YM" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_G } , std::bind(&CTestCharacter::Rot , std::ref(*this) , 3));
	CInputManager::GetInstance().AddAction("ZP" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_V } , std::bind(&CTestCharacter::Rot , std::ref(*this) , 4));
	CInputManager::GetInstance().AddAction("ZM" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_B } , std::bind(&CTestCharacter::Rot , std::ref(*this) , 5));
	CInputManager::GetInstance().AddAction("Destroy" , EButtonOption::TRIGGER , *this , { EButtonType::KEYBOARD,DIK_L } , std::bind(&CActor::Destroy , std::ref(*this)));
	CInputManager::GetInstance().AddAction("CCMove" , EButtonOption::TRIGGER , *this , { EButtonType::KEYBOARD,DIK_C } , std::bind(&CTestCharacter::ChangeCameraMove , std::ref(*this)));
	CInputManager::GetInstance().AddAction("CCMode" , EButtonOption::TRIGGER , *this , { EButtonType::KEYBOARD,DIK_X } , std::bind(&CTestCharacter::ChangeCameraMode , std::ref(*this)));
}

void CTestCharacter::Move(int num)
{
	if(num == 0)
	{
		XMFLOAT3 fv = Transform.GetForwardVector();

		Transform.Location.x += fv.x * 1;
		Transform.Location.y += fv.y * 1;
		Transform.Location.z += fv.z * 1;
	}
	else if(num == 1)
	{
		XMFLOAT3 fv = Transform.GetForwardVector();

		Transform.Location.x -= fv.x * 1;
		Transform.Location.y -= fv.y * 1;
		Transform.Location.z -= fv.z * 1;
	}
}

void CTestCharacter::ChangeCameraMove()
{
	CComponent* buf;
	if(GetComponent<CSpringArmComponent>(buf))
	{
		CSpringArmComponent* spr = dynamic_cast<CSpringArmComponent*>(buf);
		if(spr->GetSyncMode() == ESyncMode::ALL_SYNC)
		{
			spr->SetSyncMode(ESyncMode::LOCATION_ONLY_SYNC);
		}
		else
		{
			spr->SetSyncMode(ESyncMode::ALL_SYNC);
		}
	}
}

void CTestCharacter::ChangeCameraMode()
{
	static int cnt = 0;

	cnt++;

	CComponent* buf;
	if(GetComponent<CCameraComponent>(buf))
	{
		CCameraComponent* camera = dynamic_cast<CCameraComponent*>(buf);
		if(cnt % 2 == 0)
		{
			camera->SetView({ 0.f,0.f,-100.f } , { 0.f,0.f,0.f } , { 0.f,1.f,0.f });
			if(GetComponent<CSpringArmComponent>(buf))
			{
				CSpringArmComponent* spr = dynamic_cast<CSpringArmComponent*>(buf);
				spr->SetLerpTime(1.0f);
			}
		}
		else
		{
			camera->SetView({ 0.f,0.f,-10.f } , { 0.f,0.f,0.f } , { 0.f,1.f,0.f });
			if(GetComponent<CSpringArmComponent>(buf))
			{
				CSpringArmComponent* spr = dynamic_cast<CSpringArmComponent*>(buf);
				spr->SetLerpTime(0.0f);
				//spr->SetSyncMode(ESyncMode::ALL_SYNC);
			}
		}
	}
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
	default:
		break;
	}
}

void CTestCharacter::CollisionAction(CActor& collideActor)
{
	if(collideActor.HasTag("Dice"))
	{
		collideActor.Destroy();
		//CGameManager::GetInstance().SetIsPause(true);
	}
}