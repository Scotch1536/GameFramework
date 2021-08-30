#include <random>
#include "CAttachObject.h"

CAttachObject::CAttachObject(ILevel& partner):CActor(partner)
{

}

void CAttachObject::EventAtBeginCollide(CActor& collideActor)
{
	if(collideActor.HasTag("Fighter"))
	{
		XMFLOAT3 loc = collideActor.Transform.GetWorldLocation();
		Transform.Location.x -= loc.x;
		Transform.Location.y -= loc.y;
		Transform.Location.z -= loc.z;

		collideActor.Transform.AttachTransform(Transform);
	}
}