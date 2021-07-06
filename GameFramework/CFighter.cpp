#include "CFighter.h"

#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Components/CAABBColliderComponent.h"
#include "GameFramework/Components/CLightComponent.h"
#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CSpringArmComponent.h"

#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Game/CApplication.h"

CFighter::CFighter(ILevel& owner):CActor(owner)
{
	CStaticMeshComponent& mesh = *new CStaticMeshComponent(*this , CModelDataManager::GetInstance().GetModel("Assets/Fighter01/Su-27.fbx" , "Assets/Fighter01/textures/") ,
		"Shader/vs.hlsl" , "Shader/ps.hlsl");

	mesh.Transform.Rotation.Angle.x = -90.f;
	mesh.Transform.Rotation.Angle.z = 180.f;

	CLightComponent& light = *new CLightComponent(*this);

	CCameraComponent& camera = *new CCameraComponent(*this);

	camera.SetProjection(10.f , 10000.f , XM_PI / 4.f , CApplication::CLIENT_WIDTH , CApplication::CLIENT_HEIGHT);
	camera.SetView({ 0.f,0.f,-50.f } , Transform.Location , { 0.f,1.f,0.f });

	CSpringArmComponent& spr = *new CSpringArmComponent(*this , Transform , camera);
	spr.SetLerpTime(1.0f);

	light.SetEyePos(camera.GetEye());
	light.SetLightPos(XMFLOAT4(1.f , 1.f , -1.f , 0.f));
	light.SetAmbient(XMFLOAT4(0.1f , 0.1f , 0.1f , 0.0f));

	/*CSphereColliderComponent& sphereCllider = *new CSphereColliderComponent(*this , mesh.GetModel() , mesh.Transform);
	sphereCllider.BindCollisionAction(std::bind(&CFighter::CollisionAction , std::ref(*this) , std::placeholders::_1));*/
	CAABBColliderComponent& aabb = *new CAABBColliderComponent(*this , mesh.GetModel() , Transform);
	aabb.BindCollisionAction(std::bind(&CFighter::CollisionAction , std::ref(*this) , std::placeholders::_1));

	CInputManager::GetInstance().AddAction("Move" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_W } , std::bind(&CFighter::Move , std::ref(*this)));
	CInputManager::GetInstance().AddAction("XP" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_R } , std::bind(&CFighter::Rot , std::ref(*this) , 0));
	CInputManager::GetInstance().AddAction("XM" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_T } , std::bind(&CFighter::Rot , std::ref(*this) , 1));
	CInputManager::GetInstance().AddAction("YP" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_F } , std::bind(&CFighter::Rot , std::ref(*this) , 2));
	CInputManager::GetInstance().AddAction("YM" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_G } , std::bind(&CFighter::Rot , std::ref(*this) , 3));
	CInputManager::GetInstance().AddAction("ZP" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_V } , std::bind(&CFighter::Rot , std::ref(*this) , 4));
	CInputManager::GetInstance().AddAction("ZM" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_B } , std::bind(&CFighter::Rot , std::ref(*this) , 5));
}

void CFighter::Move()
{
	XMFLOAT3 fv = Transform.GetForwardVector();

	Transform.Location.x += fv.x * 1;
	Transform.Location.y += fv.y * 1;
	Transform.Location.z += fv.z * 1;
}

void CFighter::Rot(int num)
{
	switch(num)
	{
	case 0:
		Transform.Rotation.Angle.x--;
		return;
	case 1:
		Transform.Rotation.Angle.x++;
		return;
	case 2:
		Transform.Rotation.Angle.y--;
		return;
	case 3:
		Transform.Rotation.Angle.y++;
		return;
	case 4:
		Transform.Rotation.Angle.z++;
		return;
	case 5:
		Transform.Rotation.Angle.z--;
		return;
	}
}

void CFighter::CollisionAction(CActor& collideActor)
{
	if(collideActor.HasTag("Dice"))
	{
		isHit = true;
	}
}

void CFighter::Tick()
{
	isHit = false;
}