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
	//スカイドーム作成
	CSkyDome& skyDome = *new CSkyDome(*this);

	////カメラ作成
	//CCameraActor& camera = *new CCameraActor(*this);

	////アクタージェネレーター作成
	//new CActorGenerator(*this , [&] { return new CAttachObject(*this); } , { -40.0f,-20.0f,40.0f } , { 40.0f,20.0f,50.0f } , 5.0f);

	//ライト設定
	CLightManager::GetInstance().SetDirectionLight({ 1.0f,1.0f,-1.0f });
	CLightManager::GetInstance().SetAmbientLight({ 0.1f,0.1f,0.1f });

	//カメラをレベルに設定
	//RequestSetCamera(*camera.mCamera);

	//2Dディスプレイテクスチャアクターを作成
	CDisplay2DActor& title = *new CDisplay2DActor(*this , "Assets/Textures/Decal/Title.png");
	title.Transform.Scale = { static_cast<float>(CApplication::CLIENT_WIDTH),static_cast<float>(CApplication::CLIENT_HEIGHT),0.0f };
	title.Transform.Location.x = static_cast<float>(CApplication::CLIENT_WIDTH / 2.0f);
	title.Transform.Location.y = static_cast<float>(CApplication::CLIENT_HEIGHT / 2.0f);

	//音情報作成
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/button_click.wav" , 0.2f , false , "CLICK");
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/title_bgm.wav" , 0.1f , true , "BGM");

	//BGMを流す
	CSoundManager::GetInstance().PlaySound("BGM");

	//入力イベントの登録
	CInputManager::GetInstance().AddEvent("TitleEnd" , EButtonOption::TRIGGER , *this , { {EButtonType::MOUSE,EMouseButtonType::L_BUTTON},{EButtonType::KEYBOARD,DIK_SPACE} } , std::bind(&CTitle::End , std::ref(*this)));
}

void CTitle::End()
{
	new CMainGameLevel(mOwnerInterface , true);
	CSoundManager::GetInstance().PlaySound("CLICK");
	CInputManager::GetInstance().DeleteEvent("TitleEnd");
}