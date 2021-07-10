#include "CTestPlane.h"
#include "GameFramework/Components/CPlaneMeshComponent.h"
#include "GameFramework/Components/CBillboardComponent.h"

CTestPlane::CTestPlane(ILevel& partner):CActor(partner)
{
	CBillboardComponent& mesh = *new CBillboardComponent(*this , Transform , "Assets/dice/BLUE_PAPER.png");
	mesh.Transform.Scale = { 50.0f,50.0f,1.0f };
	//mesh.Transform.Rotation.SetAngle({ 0.0f,0.0f,0.0f });
}