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
	/*
	★超重要★
	コンポーネントはコンストラクタの引数ownerにいれたアクターに自動で追加される
	その際原則ヒープ領域に(newで)作成すること
	*/
	CStaticMeshComponent& staticMesh = *new CStaticMeshComponent(*this , CModelDataManager::GetInstance().GetModel("./Assets/dice/PlayerBox.x" , "assets/dice/") ,
		"Shader/vs.hlsl" , "Shader/ps.hlsl");

	//CAABBColliderComponent& aabb = *new CAABBColliderComponent(*this , staticMesh.GetModel() , Transform);
	CSphereColliderComponent* sphereCllider = new CSphereColliderComponent(*this , staticMesh.GetModel() , Transform);

	//タグ追加
	AddTag("Dice");

	/*
	★超重要★
	ボタンの入力で呼びだしたいメソッドはこのようにインプットマネージャーに追加できる
	他にも追加方法があるのでインプットマネージャーのヘッダーを確認することを推奨
	*/
	CInputManager::GetInstance().AddAction("Test" , EButtonOption::TRIGGER , *this , { EButtonType::KEYBOARD,DIK_A } , std::bind(&CDice::GamePause , std::ref(*this)));
	//CInputManager::GetInstance().AddAction("XP" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_S } , std::bind(&CDice::Rot , std::ref(*this) , 0));
	//CInputManager::GetInstance().AddAction("XM" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_D } , std::bind(&CDice::Rot , std::ref(*this) , 1));
	//CInputManager::GetInstance().AddAction("YP" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_F } , std::bind(&CDice::Rot , std::ref(*this) , 2));
	//CInputManager::GetInstance().AddAction("YM" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_G } , std::bind(&CDice::Rot , std::ref(*this) , 3));
	//CInputManager::GetInstance().AddAction("ZP" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_H } , std::bind(&CDice::Rot , std::ref(*this) , 4));
	//CInputManager::GetInstance().AddAction("ZM" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_J } , std::bind(&CDice::Rot , std::ref(*this) , 5));
	//CInputManager::GetInstance().AddAction("CameraMove" , EButtonOption::PRESS , *this , { EButtonType::KEYBOARD,DIK_K } , std::bind(&CDice::Rot , std::ref(*this) , 6));
}

void CDice::GamePause()
{
	CGameManager::GetInstance().SetIsPause(false);
}

void CDice::Rot(int dire)
{
	switch(dire)
	{
	case 0:
		Transform.Rotation.Angle.x++;
		return;
	case 1:
		Transform.Rotation.Angle.x--;
		return;
	case 2:
		Transform.Rotation.Angle.y++;
		return;
	case 3:
		Transform.Rotation.Angle.y--;
		return;
	case 4:
		Transform.Rotation.Angle.z++;
		return;
	case 5:
		Transform.Rotation.Angle.z--;
		return;
	default:
		break;
	}
}