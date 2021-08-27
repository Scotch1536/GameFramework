#include "CBullet.h"
#include "GameFramework/Components/CSphereMeshComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"

CBullet::CBullet(ILevel& partner , XMFLOAT3 initLocation , XMFLOAT3 direction , int destroyFrame)
	:CActor(partner) ,
	mDirection(direction) , mDestroyFrame(destroyFrame)
{
	AddTag("Bullet");

	CSphereMeshComponent& mesh = *new CSphereMeshComponent(*this , Transform , { 1.0f,1.0f,0.0f,1.0f });
	mesh.Transform.Location = initLocation;
	mesh.Transform.Scale = { 2.0f,2.0f,2.0f };

	CSphereColliderComponent& collider = *new CSphereColliderComponent(*this , mesh.Transform);
	collider.SetObjectType("Bullet");
}

void CBullet::Tick()
{
	mFrame++;

	Transform.Location.x += mDirection.x*10.0f;
	Transform.Location.y += mDirection.y*10.0f;
	Transform.Location.z += mDirection.z*10.0f;

	if(mFrame == mDestroyFrame)
	{
		Destroy();
	}
}