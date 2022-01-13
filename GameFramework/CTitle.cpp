#include "GameFramework/Actor/CDisplay2DActor.h"
#include "GameFramework/Actor/CCameraActor.h"
#include "GameFramework/Actor/CActorGenerator.h"
#include "GameFramework/Game/CApplication.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CSoundManager.h"
#include "GameFramework/Managers/CLightManager.h"
#include "GameFramework/Components/CParticleGeneratorComponent.h"
#include "GameFramework/Components/CSphereMeshComponent.h"

#include "CSkyDome.h"
#include "CAttachObject.h"
#include "CMainGameLevel.h"
#include "CTitle.h"

void CTitle::Init()
{
	//�X�J�C�h�[���쐬
	CSkyDome& skyDome = *new CSkyDome(*this);

	//�J�����쐬
	CCameraActor& camera = *new CCameraActor(*this);

	//�A�N�^�[�W�F�l���[�^�[�쐬
	//new CActorGenerator(*this , [&] { return new CAttachObject(*this); } , { -40.0f,-20.0f,40.0f } , { 40.0f,20.0f,50.0f } , 5.0f);

	//�p�[�e�B�N���A�N�^�[�p�̋�A�N�^�[�쐬
	mParticle = new CActor(*this);

	//�p�[�e�B�N���쐬���ɍs���U�����̍쐬
	auto createParticle = [&](CActor& actor)
	{
		CSphereMeshComponent& sphere = *new CSphereMeshComponent(actor , actor.Transform);
		sphere.Transform.Scale = { 2.0f,2.0f,2.0f };
	};

	//�R�[���p�[�e�B�N���쐬
	new CParticleGeneratorComponent(*mParticle , createParticle , 2.0f , 2.0f , 30.0f , *new CParticleBaseGeneratorLine({ 0.0f,1.0f,0.0f }),100);
	mParticle->Transform.Location.y = -25.0f;
	mParticle->Transform.Location.z = 100.0f;

	//���C�g�ݒ�
	CLightManager::GetInstance().SetDirectionLight({ 1.0f,1.0f,-1.0f });
	CLightManager::GetInstance().SetAmbientLight({ 0.1f,0.1f,0.1f });

	//�J���������x���ɐݒ�
	RequestSetCamera(*camera.mCamera);

	//2D�f�B�X�v���C�e�N�X�`���A�N�^�[���쐬
	//CDisplay2DActor& title = *new CDisplay2DActor(*this , "Assets/Textures/Decal/AttachTitle.png");
	//title.Transform.Scale = { 600.0f,300.0f,0.0f };
	//title.Transform.Location.x = static_cast<float>(CApplication::CLIENT_WIDTH / 2.0f);
	//title.Transform.Location.y = (200.0f);
	//CDisplay2DActor& pressSpace = *new CDisplay2DActor(*this , "Assets/Textures/Decal/PressSpace.png");
	//pressSpace.Transform.Scale = { 600.0f,300.0f,0.0f };
	//pressSpace.Transform.Location.x = static_cast<float>(CApplication::CLIENT_WIDTH / 2.0f);
	//pressSpace.Transform.Location.y = (500.0f);

	//�����쐬
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/button_click.wav" , 0.2f , false , "CLICK");
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/title_bgm.wav" , 0.1f , true , "BGM");

	//BGM�𗬂�
	CSoundManager::GetInstance().PlaySound("BGM");

	//���̓C�x���g�̓o�^
	CInputManager::GetInstance().AddEvent("TitleEnd" , EButtonOption::TRIGGER , *this , { {EButtonType::MOUSE,EMouseButtonType::L_BUTTON},{EButtonType::KEYBOARD,DIK_SPACE} } , std::bind(&CTitle::End , std::ref(*this)));
}

void CTitle::Tick()
{
	mCounter++;
	if(mParticle != nullptr)
	{
		mParticle->Transform.Location.z++;
		mParticle->Transform.Rotation.AddAngle({ 0.0f,0.0f,2.0f });

		if(mCounter > 50)
		{
			mParticle->Destroy();
			mParticle = nullptr;
		}
	}
}

void CTitle::End()
{
	new CTitle(mOwnerInterface , true);
	CSoundManager::GetInstance().PlaySound("CLICK");
	CInputManager::GetInstance().DeleteEvent("TitleEnd");
}