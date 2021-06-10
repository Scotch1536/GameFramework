#include <functional>

#include "CDice.h"
#include "CStaticMeshComponent.h"
#include "InternalCode/CLevel.h"

#include "ExternalCode/CDirectInput.h"
#include "InternalCode/CCameraComponent.h"
#include "InternalCode/CLightComponent.h"
#include "ExternalCode/Application.h"
#include "InternalCode/CInputManager.h"
#include "InternalCode/CModelDataManager.h"

CDice::CDice(CLevel& owner):CActor(owner)
{
	/*
	★超重要★
	コンポーネントはコンストラクタの引数ownerにいれたアクターに自動で追加される
	その際原則ヒープ領域に(newで)作成すること
	*/
	CStaticMeshComponent* staticMesh = new CStaticMeshComponent(*this , CModelManager::GetInstance().GetModel("assets/dice/PlayerBox.x" , "assets/dice/"));
	CCameraComponent* camera = new CCameraComponent(*this);
	CLightComponent* light = new CLightComponent(*this);

	camera->SetProjection(10.f , 10000.f , XM_PI / 4.f , Application::CLIENT_WIDTH , Application::CLIENT_HEIGHT);
	camera->SetView({ 0.f,0.f,-100.f } , { 0.f,0.f,0.f } , { 0.f,1.f,0.f });

	light->SetEyePos(camera->GetEye());
	light->SetLightPos(XMFLOAT4(1.f , 1.f , -1.f , 0.f));
	light->SetAmbient(XMFLOAT4(0.f , 0.f , 0.f , 0.f));

	/*
	★超重要★
	ボタンの入力で呼びだしたいメソッドはこのようにインプットマネージャーに追加できる
	他にも追加方法があるのでインプットマネージャーのヘッダーを確認することを推奨
	*/
	CInputManager::GetInstance().AddAction("Test" , *this , { EButtonType::KEYBOARD,DIK_A } , std::bind(&CDice::Test , std::ref(*this)));
	CInputManager::GetInstance().AddAction("XP" , *this , { EButtonType::KEYBOARD,DIK_S } , std::bind(&CDice::Rot , std::ref(*this) , 0));
	CInputManager::GetInstance().AddAction("XM" , *this , { EButtonType::KEYBOARD,DIK_D } , std::bind(&CDice::Rot , std::ref(*this) , 1));
	CInputManager::GetInstance().AddAction("YP" , *this , { EButtonType::KEYBOARD,DIK_F } , std::bind(&CDice::Rot , std::ref(*this) , 2));
	CInputManager::GetInstance().AddAction("YM" , *this , { EButtonType::KEYBOARD,DIK_G } , std::bind(&CDice::Rot , std::ref(*this) , 3));
	CInputManager::GetInstance().AddAction("ZP" , *this , { EButtonType::KEYBOARD,DIK_H } , std::bind(&CDice::Rot , std::ref(*this) , 4));
	CInputManager::GetInstance().AddAction("ZM" , *this , { EButtonType::KEYBOARD,DIK_J } , std::bind(&CDice::Rot , std::ref(*this) , 5));
	CInputManager::GetInstance().AddAction("CameraMove" , *this , { EButtonType::KEYBOARD,DIK_K } , std::bind(&CDice::Rot , std::ref(*this) , 6));
	CInputManager::GetInstance().AddAction("Destroy" , *this , { EButtonType::KEYBOARD,DIK_L } , std::bind(&CActor::Destroy , std::ref(*this)));
}

void CDice::Test()
{
	MessageBox(NULL , "Test" , "error" , MB_OK);
}

void CDice::Rot(int dire)
{
	switch(dire)
	{
	case 0:
		mTransform.Rotation.Angle.x++;
		return;
	case 1:
		mTransform.Rotation.Angle.x--;
		return;
	case 2:
		mTransform.Rotation.Angle.y++;
		return;
	case 3:
		mTransform.Rotation.Angle.y--;
		return;
	case 4:
		mTransform.Rotation.Angle.z++;
		return;
	case 5:
		mTransform.Rotation.Angle.z--;
		return;
	case 6:
		CComponent* buf;
		if(GetComponentFromAttribute(CComponent::EAttribute::CAMERA , buf))
		{
			CCameraComponent* camera = dynamic_cast<CCameraComponent*>(buf);
			XMFLOAT3 eye = camera->GetEye();
			eye.x += 2;
			camera->SetEye(eye);
		}
		return;
	default:
		break;
	}
}