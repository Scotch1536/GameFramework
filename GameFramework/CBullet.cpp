#include "GameFramework/Components/CSphereMeshComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Managers/CGameManager.h"

#include "CBullet.h"

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
	float dt = CGameManager::GetInstance().GetDeltaTime();

	mFrame++;

	Transform.Location.x += mDirection.x*(500.0f*dt);
	Transform.Location.y += mDirection.y*(500.0f*dt);
	Transform.Location.z += mDirection.z*(500.0f*dt);

	if(mFrame == mDestroyFrame)
	{
		Destroy();
	}
}