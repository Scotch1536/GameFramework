#include "CDrawAxis.h"

#include "GameFramework/Components/CLineComponent.h"

CDrawAxis::CDrawAxis(ILevel& partner, CTransform& parentTrans) :CActor(partner)
{

	XMFLOAT4 red = { 1.0f,0.0f ,0.0f ,1.0f };
	XMFLOAT4 green = { 0.0f,1.0f ,0.0f ,1.0f };
	XMFLOAT4 blue = { 0.0f,0.0f ,1.0f ,1.0f };

	CLineComponent& axisX = *new CLineComponent(*this, parentTrans.GetWorldLocation(), parentTrans.GetForwardVector(),
												200.0f, red, &parentTrans);
	CLineComponent& axisY = *new CLineComponent(*this, parentTrans.GetWorldLocation(), parentTrans.GetUpwardVector(),
												200.0f, green, &parentTrans);
	CLineComponent& axisZ = *new CLineComponent(*this, parentTrans.GetWorldLocation(), parentTrans.GetRightVector(),
												200.0f, blue, &parentTrans);
}