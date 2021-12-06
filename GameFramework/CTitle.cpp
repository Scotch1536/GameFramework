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

	CDisplay2DActor& aurora = *new CDisplay2DActor(*this , "Assets/Textures/Anim/dora01.png");
	aurora.Transform.Scale = { 500.0f,500.0f,0.0f };
	aurora.Transform.Location.x = static_cast<float>(CApplication::CLIENT_WIDTH / 2.0f);
	aurora.Transform.Location.y = static_cast<float>(CApplication::CLIENT_HEIGHT / 2.0f);

	auto updateVertex = [&]
	{
		aurora.GetDisplay2D().UpdateVertexBuffer();
	};
	anim = new C2DAnimationComponent(aurora , 3 , 4);
	anim->AddAnimData(aurora.GetDisplay2D().GetUV(0) , aurora.GetDisplay2D().GetUV(1) , aurora.GetDisplay2D().GetUV(2) , aurora.GetDisplay2D().GetUV(3) , updateVertex , "Dragon");
	anim->AddAnimInfo("mot1" , 0 , 2 , 0.5f , true);
	anim->AddAnimInfo("mot1" ,3.5f , false);
	anim->AddAnimInfo("mot2" , 3 , 5 , 0.5f , true);
	anim->AddAnimInfo("mot3" , 6 , 8 , 0.5f , true);
	anim->Play("mot1" , "Dragon");

	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/button_click.wav" , 0.2f , false , "CLICK");
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/title_bgm.wav" , 0.1f , true , "BGM");

	CSoundManager::GetInstance().PlaySound("BGM");

	CInputManager::GetInstance().AddEvent("TitleEnd" , EButtonOption::TRIGGER , *this , { {EButtonType::MOUSE,EMouseButtonType::L_BUTTON},{EButtonType::KEYBOARD,DIK_SPACE} } , std::bind(&CTitle::End , std::ref(*this)));
	CInputManager::GetInstance().AddEvent("Test" , EButtonOption::TRIGGER , *this , { EButtonType::KEYBOARD,DIK_2 } , std::bind(&CTitle::Test , std::ref(*this)));
	CInputManager::GetInstance().AddEvent("Test2" , EButtonOption::TRIGGER , *this , { EButtonType::KEYBOARD,DIK_3 } , std::bind(&CTitle::Test2 , std::ref(*this)));
}

void CTitle::Test()
{
	anim->Play("mot2" , "Dragon");
}

void CTitle::Test2()
{
	anim->Stop("Dragon");
}

void CTitle::End()
{
	new CMainGameLevel(mOwnerInterface , true);
	CSoundManager::GetInstance().PlaySound("CLICK");
	CInputManager::GetInstance().DeleteEvent("TitleEnd");
}