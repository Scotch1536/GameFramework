//!
//! @file
//! @brief �^�C�g�����x���̃\�[�X�t�@�C��
//!

#include "GameFramework/Actor/CDisplay2DActor.h"
#include "GameFramework/Game/CApplication.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CSoundManager.h"

#include "CMainGameLevel.h"
#include "CTitle.h"

void CTitle::Init()
{
	//2D�f�B�X�v���C�e�N�X�`���A�N�^�[���쐬&������
	CDisplay2DActor& title = *new CDisplay2DActor(*this , "Assets/Textures/Decal/Title.png");
	title.Transform.Scale = { static_cast<float>(CApplication::CLIENT_WIDTH),static_cast<float>(CApplication::CLIENT_HEIGHT),0.0f };
	title.Transform.Location.x = static_cast<float>(CApplication::CLIENT_WIDTH / 2.0f);
	title.Transform.Location.y = static_cast<float>(CApplication::CLIENT_HEIGHT / 2.0f);

	//�T�E���h���쐬
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/button_click.wav" , 0.2f , false , "CLICK");
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/title_bgm.wav" , 0.1f , true , "BGM");

	//BGM�𗬂�
	CSoundManager::GetInstance().PlaySound("BGM");

	//���̓C�x���g�̓o�^
	CInputManager::GetInstance().AddEvent("TitleEnd" , EButtonOption::TRIGGER , *this , { {EMouseButtonType::L_BUTTON},{EButtonType::KEYBOARD,DIK_SPACE} } , std::bind(&CTitle::End , std::ref(*this)));
}

void CTitle::End()
{
	//�N���b�N���Đ�
	CSoundManager::GetInstance().PlaySound("CLICK");

	//���C���Q�[�����x���ɑJ��
	new CMainGameLevel(mOwnerInterface , true);

	//���̓C�x���g�̍폜
	CInputManager::GetInstance().DeleteEvent("TitleEnd");
}