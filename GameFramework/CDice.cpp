#include <functional>

#include "CDice.h"
#include "CStaticMeshComponent.h"
#include "ExternalCode/CDirectInput.h"
#include "InternalCode/CCameraComponent.h"
#include "ExternalCode/Application.h"
#include "InternalCode/CInputManager.h"
#include "InternalCode/CModelDataManager.h"

CDice::CDice(CLevel& owner):CActor(owner)
{
	CStaticMeshComponent* staticMesh = new CStaticMeshComponent(*this , CModelManager::GetInstance().GetModel("assets/HAL/halchan1.pmx" , "assets/HAL/"));
	CCameraComponent* camera = new CCameraComponent(*this);

	DirectX::XMFLOAT3 eye(-50 , 50 , -50);	//�J�����ʒu
	DirectX::XMFLOAT3 lookat(0 , 0 , 0);	//�����_
	DirectX::XMFLOAT3 up(0 , 1 , 0);		//�J�����̏�����x�N�g��

	camera->Init(
		10.0f ,							//�j�A�N���b�v
		10000.0f ,						//�t�@�[�N���b�v
		XM_PI / 4.0f ,					//����p
		Application::CLIENT_WIDTH ,		//�X�N���[����
		Application::CLIENT_HEIGHT ,	//�X�N���[���̍���
		eye , lookat , up);

	SButtonInfo bufin = { EButtonType::KEYBOARD,DIK_A };

	CInputManager::GetInstance().AddAction("test" , bufin , std::bind(&CDice::Test , std::ref(*this)));
}

void CDice::Test()
{
	MessageBox(NULL , "Test" , "error" , MB_OK);
}