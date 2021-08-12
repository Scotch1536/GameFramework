#include "CDrawAxis.h"

#include "GameFramework/Components/CLineComponent.h"

CDrawAxis::CDrawAxis(ILevel& partner, CTransform& parentTrans) :CActor(partner),Transform(parentTrans)
{
	XMFLOAT4 red = { 1.0f,0.0f ,0.0f ,1.0f };

	CLineComponent& axis = *new CLineComponent(*this, Transform.GetWorldLocation(), Transform.GetForwardVector(),
												200.0f, red, &Transform);
}