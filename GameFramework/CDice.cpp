#include "CDice.h"
#include "CStaticMeshComponent.h"
#include "InternalCode/CCameraComponent.h"
#include "ExternalCode/Application.h"

CDice::CDice(CLevel& owner):CActor(owner)
{
	CStaticMeshComponent* staticMesh = new CStaticMeshComponent(*this);
	CCameraComponent* camera = new CCameraComponent(*this);

	staticMesh->SetModel("assets/dice/PlayerBox.x" , "assets/dice/");

	DirectX::XMFLOAT3 eye(70 , 100 , -150);	//カメラ位置
	DirectX::XMFLOAT3 lookat(0 , 0 , 0);	//注視点
	DirectX::XMFLOAT3 up(0 , 1 , 0);		//カメラの上向きベクトル

	camera->Init(
		10.0f ,							//ニアクリップ
		10000.0f ,						//ファークリップ
		XM_PI / 4.0f ,					//視野角
		Application::CLIENT_WIDTH ,		//スクリーン幅
		Application::CLIENT_HEIGHT ,	//スクリーンの高さ
		eye , lookat , up);
}