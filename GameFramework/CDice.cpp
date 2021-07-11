#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CLightComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Components/CAABBColliderComponent.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Managers/CGameManager.h"

#include "CDice.h"

CDice::CDice(CLevel& owner):CActor(owner , false)
{
	CStaticMeshComponent& staticMesh = *new CStaticMeshComponent(*this , Transform ,
		CModelDataManager::GetInstance().GetModel("./Assets/Models/dice/PlayerBox.x" , "Assets/Models/dice/") ,
		"Shader/vs.hlsl" , "Shader/ps.hlsl");

	CSphereColliderComponent* sphereCllider = new CSphereColliderComponent(*this , staticMesh.GetModel() , Transform);

	//タグ追加
	AddTag("Dice");
}
