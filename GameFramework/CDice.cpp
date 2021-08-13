#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Components/CAABBColliderComponent.h"
#include "GameFramework/Components/CVisionComponent.h"
#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Managers/CSoundManager.h"

#include "CDice.h"

CDice::CDice(ILevel& owner , XMFLOAT3& pointLocation):CActor(owner , false)
{
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/bomb.wav" , 0.1f , false , "BOMB");

	CStaticMeshComponent& staticMesh = *new CStaticMeshComponent(*this , Transform ,
		CModelDataManager::GetInstance().GetModel("./Assets/Models/dice/PlayerBox.x" , "Assets/Models/dice/") ,
		"Shader/vs.hlsl" , "Shader/ps.hlsl");

	//CSphereColliderComponent* sphereCllider = new CSphereColliderComponent(*this , staticMesh.GetModel() , Transform);
	CAABBColliderComponent* AABBCllider = new CAABBColliderComponent(*this , staticMesh.GetModel() , Transform);

	CVisionComponent* vision = new CVisionComponent(*this , Transform , 500 , 25 , std::bind(&CDice::Look , std::ref(*this) , std::placeholders::_1));

	Transform.Rotation.SetAngle({ 0.f, 180.f, 0.f });

	Transform.RequestDebugLine();

	//タグ追加
	AddTag("Dice");
}

void CDice::Move()
{
	XMFLOAT3 fv = Transform.GetForwardVector();

	Transform.Location.x += fv.x * 1.25;
	Transform.Location.y += fv.y * 1.25;
	Transform.Location.z += fv.z * 1.25;
}

void CDice::Look(CActor& collideActor)
{
	if(collideActor.HasTag("Fighter"))
	{
		Transform.Rotation.ChangeAngleAndQuaternionToLocation(collideActor.Transform.GetWorldLocation());
		Move();
	}
}

void CDice::EventAtBeginCollide(CActor& collideActor)
{
	if(collideActor.HasTag("Bullet"))
	{
		Destroy();
		collideActor.Destroy();

		CSoundManager::GetInstance().PlaySound("BOMB");
	}
}
