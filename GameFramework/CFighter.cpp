#include "CFighter.h"

#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Components/CAABBColliderComponent.h"
#include "GameFramework/Components/CLightComponent.h"
#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CSpringArmComponent.h"

#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CSoundManager.h"
#include "GameFramework/Game/CApplication.h"

#include "CBullet.h"

CFighter::CFighter(ILevel& owner):CActor(owner) , mPointer(*new CPointer(owner , *this))
{
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/shot.wav" , 0.05f , false , "SHOT");

	CStaticMeshComponent& mesh = *new CStaticMeshComponent(*this , Transform ,
		CModelDataManager::GetInstance().GetModel("Assets/Models/Fighter/F-15E.fbx" , "Assets/Models/Fighter/Textures/") ,
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

	CInputManager::GetInstance().AddEvent("Shot" , EButtonOption::PRESS , *this , { EButtonType::MOUSE,EMouseButtonType::L_BUTTON } , std::bind(&CFighter::Shot , std::ref(*this)));
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

	XMFLOAT3 loc = Transform.Location;
	XMFLOAT3 fv = Transform.GetForwardVector();

	loc.x += fv.x * 10.0f;
	loc.y += fv.y * 10.0f;
	loc.z += fv.z * 10.0f;

	new CBullet(mOwnerInterface , loc , Transform.GetForwardVector() , 60 * 5);

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

void CFighter::Rot()
{
	//Transform.Rotation.ChangeAngleAndQuaternionToLocation(mPointer.Transform.Location);

	if(mTargetRot == nullptr)
	{
		XMFLOAT4& qua = *new XMFLOAT4;
		Transform.Rotation.CalcQuaternionToLocation(mPointer.Transform.Location , qua);
		mTargetRot.reset(&qua);
		mStartRot = Transform.Rotation.GetQuaternion();
		mAlpha = 0.0f;
		mIncrementAlpha = 1.0f / (60.0f * 0.15f);
	}
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