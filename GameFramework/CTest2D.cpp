#include "CTest2D.h"
#include "GameFramework/Components/CDisplay2DComponent.h"
#include "GameFramework/Game/CApplication.h"

CTest2D::CTest2D(ILevel& partner):CActor(partner)
{
	CDisplay2DComponent& mesh = *new CDisplay2DComponent(*this , Transform , "Assets/Textures/White/white.bmp");
	mesh.Transform.Scale = { 100.0f,30.0f,0.0f };
	mesh.Transform.Location.x = CApplication::CLIENT_WIDTH / 2;
	mesh.Transform.Location.y = 30*2;
}