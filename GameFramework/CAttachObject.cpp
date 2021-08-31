#include <random>

#include "GameFramework/Components/CBoxMeshComponent.h"
#include "GameFramework/Components/CAABBColliderComponent.h"
#include "GameFramework/Components/CSphereMeshComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"

#include "CAttachObject.h"

CAttachObject::CAttachObject(ILevel& partner):CActor(partner)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> colorGenerator(0.0f , 1.0f);
	std::uniform_real_distribution<float> scaleGenerator(2.0f , 20.0f);
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

}

void CAttachObject::EventAtBeginCollide(CActor& collideActor)
{
	if(collideActor.HasTag("Fighter"))
	{
		XMFLOAT3 loc = collideActor.Transform.GetWorldLocation();
		XMFLOAT3 rot = collideActor.Transform.GetWorldRotatorAngle();

		rot.x *= -1.0f;
		rot.y *= -1.0f;
		rot.z *= -1.0f;

		Transform.Location.x -= loc.x;
		Transform.Location.y -= loc.y;
		Transform.Location.z -= loc.z;
		Transform.Rotation.SetAngle(rot);

		collideActor.Transform.AttachTransform(Transform);

		XMFLOAT4 color = mMesh->GetColor();
		color.w = 0.5f;
		mMesh->SetColor(color);
	}
}