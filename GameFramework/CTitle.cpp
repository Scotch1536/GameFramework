#include "GameFramework/Actor/CDisplay2DActor.h"
#include "GameFramework/Game/CApplication.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CSoundManager.h"
#include "GameFramework/Components/C2DAnimationComponent.h"

#include "CMainGameLevel.h"
#include "CTitle.h"

void CTitle::Init()
{
	CDisplay2DActor& title = *new CDisplay2DActor(*this , "Assets/Textures/Decal/Title.png");
	title.Transform.Scale = { static_cast<float>(CApplication::CLIENT_WIDTH),static_cast<float>(CApplication::CLIENT_HEIGHT),0.0f };
	title.Transform.Location.x = static_cast<float>(CApplication::CLIENT_WIDTH / 2.0f);
	title.Transform.Location.y = static_cast<float>(CApplication::CLIENT_HEIGHT / 2.0f);

	CDisplay2DActor& aurora = *new CDisplay2DActor(*this , "Assets/Textures/Anim/Aurora.png");
	aurora.Transform.Scale = { 500.0f,500.0f,0.0f };
	aurora.Transform.Location.x = static_cast<float>(CApplication::CLIENT_WIDTH / 2.0f);
	aurora.Transform.Location.y = static_cast<float>(CApplication::CLIENT_HEIGHT / 2.0f);

	C2DAnimationComponent& anim = *new C2DAnimationComponent(aurora , 4 , 5 , 3.0f , true , aurora.GetUV(0) , aurora.GetUV(1) , aurora.GetUV(2) , aurora.GetUV(3));

	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/button_click.wav" , 0.2f , false , "CLICK");
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/title_bgm.wav" , 0.1f , true , "BGM");

	CSoundManager::GetInstance().PlaySound("BGM");

	CInputManager::GetInstance().AddEvent("TitleEnd" , EButtonOption::TRIGGER , *this , { {EButtonType::MOUSE,EMouseButtonType::L_BUTTON},{EButtonType::KEYBOARD,DIK_SPACE} } , std::bind(&CTitle::End , std::ref(*this)));
}

void CTitle::End()
{
	new CMainGameLevel(mOwnerInterface , true);
	CSoundManager::GetInstance().PlaySound("CLICK");
	CInputManager::GetInstance().DeleteEvent("TitleEnd");
}