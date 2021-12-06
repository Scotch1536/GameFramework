#pragma once
#include "../Transform/CTransform.h"
#include "../Actor/CActor.h"

#include "CComponent.h"

class CSceneComponent :public CComponent
{
public:
	CTransform Transform;

	CSceneComponent(CActor& owner , CTransform& parentTrans):CComponent(owner) , Transform(owner , parentTrans) {};
};