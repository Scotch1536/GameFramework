//!
//! @file
//! @brief �|�C���^�[�A�N�^�[�̃\�[�X�t�@�C��
//!

#include "GameFramework/Components/CBillboardComponent.h"
#include "GameFramework/Game/CApplication.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Game/CApplication.h"

#include "CFighter.h"
#include "CPointer.h"

CPointer::CPointer(ILevel& partner , CFighter& owner):CActor(partner) , mOwner(owner)
{
	//�f�B�X�v���C�̒��S���W�擾
	int displayCenterPosX = GetSystemMetrics(SM_CXSCREEN) / 2;
	int displayCenterPosY = GetSystemMetrics(SM_CYSCREEN) / 2;

	//�J�[�\���̍��W���Z�b�g
	SetCursorPos(displayCenterPosX , displayCenterPosY);

	//�}�E�X�̏������W������
	mInitMousePosX = CApplication::CLIENT_WIDTH / 2;
	mInitMousePosY = CApplication::CLIENT_HEIGHT / 2;

	//�r���{�[�h�R���|�[�l���g�ǉ�&������
	CBillboardComponent& billboard = *new CBillboardComponent(*this , Transform , "Assets/Textures/Pointer/Pointer.png");
	billboard.Transform.Scale = { 10.0f,10.0f,1.0f };
}

void CPointer::Tick()
{
	//���݂��Ȃ����
	if(mInitLocation == nullptr)
	{
		//�������P�[�V�����쐬&������
		mInitLocation.reset(new XMFLOAT3);
		*mInitLocation = mOwner.Transform.Location;
	}

	float mousePosX = CInputManager::GetInstance().GetMousePosX();
	float mousePosY = CInputManager::GetInstance().GetMousePosY();

	//�������W�Z�o
	mDiffPosX = mInitMousePosX - mousePosX;
	mDiffPosY = mInitMousePosY - mousePosY;

	//����̒���
	float posX , posY;
	posX = mDiffPosX / 6.f;
	posY = mDiffPosY / 6.f;

	//���P�[�V�����X�V
	Transform.Location.x = mInitLocation->x - posX;
	Transform.Location.y = mInitLocation->y + posY;
}