#include "CTestPlane.h"
#include "GameFramework/Components/CPlaneMeshComponent.h"

CTestPlane::CTestPlane(ILevel& partner):CActor(partner)
{
	CPlaneMeshComponent& mesh = *new CPlaneMeshComponent(*this , Transform , { 1.0f,1.0f,1.0f,1.0f });
	mesh.Transform.Scale = { 50.0f,50.0f,0.0f };
}