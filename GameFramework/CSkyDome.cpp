#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Managers/CModelDataManager.h"

#include "CSkyDome.h"

CSkyDome::CSkyDome(ILevel& owner):CActor(owner)
{
	CStaticMeshComponent& staticMesh = *new CStaticMeshComponent(*this , CModelDataManager::GetInstance().GetModel("Assets/skydome/skydome.x" , "Assets/skydome/") ,
		"Shader/vs.hlsl" , "Shader/pstexcol.hlsl");
}