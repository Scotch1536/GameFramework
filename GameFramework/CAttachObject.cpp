#include <random>

#include "GameFramework/Components/CBoxMeshComponent.h"
#include "GameFramework/Components/CAABBColliderComponent.h"
#include "GameFramework/Components/CSphereMeshComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Managers/CSoundManager.h"

#include "CAttachObject.h"

CAttachObject::CAttachObject(ILevel& partner):CActor(partner)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> colorGenerator(0.0f , 1.0f);
	std::uniform_real_distribution<float> scaleGenerator(2.0f , 20.0f);

	AddTag("AttachObject");

	CColliderComponent* collider = nullptr;

	int randomNum = mt() % 2;

	if(randomNum == 0)
	{
		CBoxMeshComponent& box = *new CBoxMeshComponent(*this , Transform , { colorGenerator(mt),colorGenerator(mt),colorGenerator(mt),0.99f });
		box.Transform.Scale = { scaleGenerator(mt),scaleGenerator(mt) ,scaleGenerator(mt) };
		mMesh = &box;

		collider = new CAABBColliderComponent(*this , box.Transform);
	}
	else if(randomNum == 1)
	{
		CSphereMeshComponent& sphere = *new CSphereMeshComponent(*this , Transform , { colorGenerator(mt),colorGenerator(mt),colorGenerator(mt),0.99f });
		sphere.Transform.Scale = { scaleGenerator(mt),scaleGenerator(mt) ,scaleGenerator(mt) };
		mMesh = &sphere;

		collider = new CSphereColliderComponent(*this , sphere.Transform);
	}

	collider->SetIsUpdate(false);
	collider->SetObjectType("AttachObject");

	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/attach.wav" , 0.1f , false , "Attach");
}

void CAttachObject::EventAtBeginCollide(CActor& collideActor)
{
	if(collideActor.HasTag("Fighter"))
	{
		XMFLOAT3 loc = collideActor.Transform.GetWorldLocation();
		XMFLOAT3 rot = collideActor.Transform.GetWorldRotatorAngle();
		XMFLOAT3 relativeVec;
		XMFLOAT3 ansVec;

		//XMFLOAT4 qua = collideActor.Transform.Rotation.GetQuaternion();
		//XMFLOAT4X4 collideActorMTX = collideActor.Transform.GetWorldMatrixResult();
		//XMFLOAT4X4 localMTX = Transform.GetWorldMatrixSelf();
		//XMFLOAT4X4 afterCTMTX;

		//LCMath::CalcMatrixMultply(localMTX , collideActorMTX , afterCTMTX);

		//XMFLOAT3 myloc;
		//mtx._41 = 0.0f;
		//mtx._42 = 0.0f;
		//mtx._43 = 0.0f;
		//LCMath::CalcFloat3MultiplyToMatrix(Transform.Location , mtx , myloc);

		LCMath::CalcFloat3FromStartToGoal(loc , Transform.Location , relativeVec);
		LCMath::CalcFloat3Dot(relativeVec , collideActor.Transform.GetRightVector() , ansVec.x);
		LCMath::CalcFloat3Dot(relativeVec , collideActor.Transform.GetUpwardVector() , ansVec.y);
		LCMath::CalcFloat3Dot(relativeVec , collideActor.Transform.GetForwardVector() , ansVec.z);

		Transform.Location = ansVec;
		rot.x *= -1.0f;
		rot.y *= -1.0f;
		rot.z *= -1.0f;
		Transform.Rotation.SetAngle(rot);
		//Transform.Rotation.SetQuaternion(qua);

		collideActor.Transform.AttachTransform(Transform);

		XMFLOAT4 color = mMesh->GetColor();
		color.w = 0.5f;
		mMesh->SetColor(color);

		CSoundManager::GetInstance().PlaySound("Attach");
		mOwnerInterface.Notice(*this);
	}
}