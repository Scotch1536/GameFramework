#pragma once
#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Components/CPrimitiveMeshComponent.h"

class CAttachObject :public CActor
{
private:
	CPrimitiveMeshComponent<>* mMesh = nullptr;
public:
	CAttachObject(ILevel& partner);

	void EventAtBeginCollide(CActor& collideActor)override;
};

