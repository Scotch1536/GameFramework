//!
//! @file
//! @brief スカイドームアクターのソースファイル
//!

#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Managers/CModelDataManager.h"

#include "CSkyDome.h"

CSkyDome::CSkyDome(ILevel& owner):CActor(owner)
{
	//スタティックメッシュコンポーネント追加&初期化
	CStaticMeshComponent& mesh = *new CStaticMeshComponent(*this , Transform ,
		CModelDataManager::GetInstance().GetModel("Assets/Models/Skydome/Dome_BB601.x" , "Assets/Models/Skydome/") ,
		"Shader/vs.hlsl" , "Shader/pstexcol.hlsl");
	mesh.Transform.Scale = { 10.0f,10.0f,10.0f };
}