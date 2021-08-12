#pragma once
#include "GameFramework/Actor/CActor.h"

class CDrawAxis :public CActor
{
private:

public:
	CTransform Transform;

	CDrawAxis(ILevel& partner, CTransform& parentTrans);
	
	//void Tick()override;
};