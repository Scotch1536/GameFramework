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

CFighter::CFighter(ILevel& owner):CActor(owner) , mPointer(*new CPointer(owner , *this))
{
	CStaticMeshComponent& mesh = *new CStaticMeshComponent(*this , Transform ,
		CModelDataManager::GetInstance().GetModel("Assets/Fighter01/Su-27.fbx" , "Assets/Fighter01/textures/") ,
		"Shader/vs.hlsl" , "Shader/ps.hlsl");

	mesh.Transform.Rotation.SetAngle({ -90.0f ,0.0f,180.0f });

	CLightComponent& light = *new CLightComponent(*this);

	CCameraComponent& camera = *new CCameraComponent(*this);

	camera.SetProjection(10.f , 10000.f , XM_PI / 4.f , CApplication::CLIENT_WIDTH , CApplication::CLIENT_HEIGHT);
	camera.SetView({ 0.f,0.f,-50.f } , Transform.Location , { 0.f,1.f,0.f });

	CSpringArmComponent& spr = *new CSpringArmComponent(*this , Transform , camera);
	spr.SetLerpTime(1.0f);

	light.SetEyePos(camera.GetEye());
	light.SetLightPos(XMFLOAT4(1.f , 1.f , -1.f , 0.f));
	light.SetAmbient(XMFLOAT4(0.1f , 0.1f , 0.1f , 0.0f));

	/*CSphereColliderComponent& sphereCllider = *new CSphereColliderComponent(*this , mesh.GetModel() , Transform);
	sphereCllider.BindCollisionAction(std::bind(&CFighter::CollisionAction , std::ref(*this) , std::placeholders::_1));*/
	CSphereColliderComponent& aabb = *new CSphereColliderComponent(*this , mesh.GetModel() , Transform);

	CInputManager::GetInstance().AddEvent("Move" , EButtonOption::PRESS , *this , { EButtonType::MOUSE,EMouseButtonType::L_BUTTON } , std::bind(&CFighter::Move , std::ref(*this)));
	CInputManager::GetInstance().AddEvent("Rot" , EButtonOption::PRESS , *this , { EButtonType::MOUSE,EMouseButtonType::R_BUTTON } , std::bind(&CFighter::Rot , std::ref(*this)));
}

void CFighter::Move()
{
	XMFLOAT3 fv = Transform.GetForwardVector();

	Transform.Location.x += fv.x * 1;
	Transform.Location.y += fv.y * 1;
	Transform.Location.z += fv.z * 1;
}

void CFighter::Rot()
{
	//Transform.Rotation.ChangeAngleAndQuaternionToLocation(mPointer.Transform.Location);

	if(mTargetRot == nullptr)
	{
		XMFLOAT4* qua = new XMFLOAT4;
		Transform.Rotation.CalcQuaternionToLocation(mPointer.Transform.Location , qua);
		mTargetRot.reset(qua);
	}
}

void CFighter::EventAtBeginCollide(CActor& collideActor)
{
	if(collideActor.HasTag("Dice"))
	{
		mIsHit = true;
	}
}

void CFighter::EventAtEndCollide(CActor& collideActor)
{
	if(collideActor.HasTag("Dice"))
	{
		mIsHit = false;
	}
}