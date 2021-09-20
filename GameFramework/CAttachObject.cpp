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
		collideActor.Transform.AttachTransform(Transform);

		XMFLOAT4 color = mMesh->GetColor();
		color.w = 0.5f;
		mMesh->SetColor(color);

		CSoundManager::GetInstance().PlaySound("Attach");
		mOwnerInterface.Notice(*this);
	}
}