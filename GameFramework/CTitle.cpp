//!
//! @file
//! @brief タイトルレベルのソースファイル
//!

#include "GameFramework/Actor/CDisplay2DActor.h"
#include "GameFramework/Game/CApplication.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CSoundManager.h"

#include "CMainGameLevel.h"
#include "CTitle.h"

void CTitle::Init()
{
	//2Dディスプレイテクスチャアクターを作成&初期化
	CDisplay2DActor& title = *new CDisplay2DActor(*this , "Assets/Textures/Decal/Title.png");
	title.Transform.Scale = { static_cast<float>(CApplication::CLIENT_WIDTH),static_cast<float>(CApplication::CLIENT_HEIGHT),0.0f };
	title.Transform.Location.x = static_cast<float>(CApplication::CLIENT_WIDTH / 2.0f);
	title.Transform.Location.y = static_cast<float>(CApplication::CLIENT_HEIGHT / 2.0f);

	//サウンド情報作成
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/button_click.wav" , 0.2f , false , "CLICK");
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/title_bgm.wav" , 0.1f , true , "BGM");

	//BGMを流す
	CSoundManager::GetInstance().PlaySound("BGM");

	//入力イベントの登録
	CInputManager::GetInstance().AddEvent("TitleEnd" , EButtonOption::TRIGGER , *this , { {EButtonType::MOUSE,EMouseButtonType::L_BUTTON},{EButtonType::KEYBOARD,DIK_SPACE} } , std::bind(&CTitle::End , std::ref(*this)));
}

void CTitle::End()
{
	//クリック音再生
	CSoundManager::GetInstance().PlaySound("CLICK");

	//メインゲームレベルに遷移
	new CMainGameLevel(mOwnerInterface , true);

	//入力イベントの削除
	CInputManager::GetInstance().DeleteEvent("TitleEnd");
}