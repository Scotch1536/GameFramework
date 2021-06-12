#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CLightComponent.h"
#include "GameFramework/Managers/CInputManager.h"

#include "CTestLevel.h"
#include "CDice.h"
#include "CTestCharacter.h"

void CTestLevel::Init()
{
	CDice& dice = *new CDice(*this);

	dice.Transform.Location = { 20.f,20.f,0.f };

	/*
	レベルから指定のアクターインスタンスのメソッドをインプットマネージャーにバインドすることは可能
	アクターからでもレベルからでもどちらでも可能だ
	*/
	//CInputManager::GetInstance().AddAction("XP" , EButtonOption::PRESS , dice , { EButtonType::KEYBOARD,DIK_S } , std::bind(&CDice::Rot , std::ref(dice) , 0));

	CTestCharacter& testChara = *new CTestCharacter(*this);

	testChara.Transform.AttachTransform(dice.Transform);

	CComponent* buf = nullptr;
	if(testChara.GetComponentFromAttribute(CComponent::EAttribute::CAMERA , buf))
	{
		CCameraComponent& camera = dynamic_cast<CCameraComponent&>(*buf);
		this->RequestSetCamera(camera);
	}
}