#include "CDice.h"
#include "CStaticMeshComponent.h"
#include "InternalCode/CCameraComponent.h"
#include "ExternalCode/Application.h"

CDice::CDice(CLevel& owner):CActor(owner)
{
	CStaticMeshComponent* staticMesh = new CStaticMeshComponent(*this);
	CCameraComponent* camera = new CCameraComponent(*this);

	staticMesh->SetModel("assets/dice/PlayerBox.x" , "assets/dice/");

	DirectX::XMFLOAT3 eye(70 , 100 , -150);	//�J�����ʒu
	DirectX::XMFLOAT3 lookat(0 , 0 , 0);	//�����_
	DirectX::XMFLOAT3 up(0 , 1 , 0);		//�J�����̏�����x�N�g��

	camera->Init(
		10.0f ,							//�j�A�N���b�v
		10000.0f ,						//�t�@�[�N���b�v
		XM_PI / 4.0f ,					//����p
		Application::CLIENT_WIDTH ,		//�X�N���[����
		Application::CLIENT_HEIGHT ,	//�X�N���[���̍���
		eye , lookat , up);
}