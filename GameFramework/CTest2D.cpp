#include "CTest2D.h"
#include "GameFramework/Components/CDisplay2DComponent.h"
#include "GameFramework/Game/CApplication.h"

CTest2D::CTest2D(ILevel& partner):CActor(partner)
{
	CDisplay2DComponent& mesh = *new CDisplay2DComponent(*this , Transform , "Assets/Textures/Decal/ãÛíÜêÌ.png");
	mesh.Transform.Scale = { 200.0f,100.0f,0.0f };

	Transform.Location.x = CApplication::CLIENT_WIDTH / 2;
	Transform.Location.y = mesh.Transform.Scale.y/2;
}