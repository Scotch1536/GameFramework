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

CDice::CDice(CLevel& owner) :CActor(owner)
{
	CStaticMeshComponent* staticMesh = new CStaticMeshComponent(*this, CModelManager::GetInstance().GetModel("assets/dice/PlayerBox.x", "assets/dice/"));
	CCameraComponent* camera = new CCameraComponent(*this);
	CLightComponent* light = new CLightComponent(*this);

	DirectX::XMFLOAT3 eye(0, 0, -100);	//カメラ位置
	DirectX::XMFLOAT3 lookat(0, 0, 0);	//注視点
	DirectX::XMFLOAT3 up(0, 1, 0);		//カメラの上向きベクトル

	camera->Init(
		10.0f,							//ニアクリップ
		10000.0f,						//ファークリップ
		XM_PI / 4.0f,					//視野角
		Application::CLIENT_WIDTH,		//スクリーン幅
		Application::CLIENT_HEIGHT,	//スクリーンの高さ
		eye, lookat, up);

	light->Init(camera->GetEye(), XMFLOAT4(1, 1, -1, 0));
	light->SetAmbient(XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f));

	CInputManager::GetInstance().AddAction("test", { EButtonType::KEYBOARD,DIK_A }, std::bind(&CDice::Test, std::ref(*this)));
	CInputManager::GetInstance().AddAction("XP", { EButtonType::KEYBOARD,DIK_S }, std::bind(&CDice::Rot, std::ref(*this), 0));
	CInputManager::GetInstance().AddAction("XM", { EButtonType::KEYBOARD,DIK_D }, std::bind(&CDice::Rot, std::ref(*this), 1));
	CInputManager::GetInstance().AddAction("YP", { EButtonType::KEYBOARD,DIK_F }, std::bind(&CDice::Rot, std::ref(*this), 2));
	CInputManager::GetInstance().AddAction("YM", { EButtonType::KEYBOARD,DIK_G }, std::bind(&CDice::Rot, std::ref(*this), 3));
	CInputManager::GetInstance().AddAction("ZP", { EButtonType::KEYBOARD,DIK_H }, std::bind(&CDice::Rot, std::ref(*this), 4));
	CInputManager::GetInstance().AddAction("ZM", { EButtonType::KEYBOARD,DIK_J }, std::bind(&CDice::Rot, std::ref(*this), 5));
	CInputManager::GetInstance().AddAction("Dst", { EButtonType::KEYBOARD,DIK_L }, std::bind(&CDice::Destroy, std::ref(*this)));
}

void CDice::Test()
{
	MessageBox(NULL, "Test", "error", MB_OK);
}

void CDice::Rot(int dire)
{
	switch (dire)
	{
	case 0:
		mTransform.rotation.angle.x++;
		break;
	case 1:
		mTransform.rotation.angle.x--;
		break;
	case 2:
		mTransform.rotation.angle.y++;
		break;
	case 3:
		mTransform.rotation.angle.y--;
		break;
	case 4:
		mTransform.rotation.angle.z++;
		break;
	case 5:
		mTransform.rotation.angle.z--;
		break;
	default:
		break;
	}
}

void CDice::Destroy()
{
	mOwnerInterface.DestroyActor(*this);
}