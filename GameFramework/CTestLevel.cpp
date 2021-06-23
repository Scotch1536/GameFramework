#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CLightComponent.h"
#include "GameFramework/Managers/CInputManager.h"

#include "CTestLevel.h"
#include "CDice.h"
#include "CTestCharacter.h"
#include "CSkyDome.h"

void CTestLevel::Init()
{
	CDice& dice = *new CDice(*this);

	dice.Transform.Location = { 0.f,20.f,0.f };

	/*
	レベルから指定のアクターインスタンスのメソッドをインプットマネージャーにバインドすることは可能
	アクターからでもレベルからでもどちらでも可能だ
	*/
	//CInputManager::GetInstance().AddAction("XP" , EButtonOption::PRESS , dice , { EButtonType::KEYBOARD,DIK_S } , std::bind(&CDice::Rot , std::ref(dice) , 0));

	CTestCharacter& testChara = *new CTestCharacter(*this);
	//testChara.Transform.Rotation.Angle.z = 180.f;
	//testChara.Transform.Rotation.Angle.y = 180.f;

	//testChara.Transform.AttachTransform(dice.Transform);

	CSkyDome& skyDome = *new CSkyDome(*this);

	CComponent* buf = nullptr;
	//std::vector<CComponent*> buf2;
	//if(testChara.GetComponentFromAttribute(CComponent::EAttribute::CAMERA , buf))
	//{
	//	CCameraComponent& camera = dynamic_cast<CCameraComponent&>(*buf);
	//	this->RequestSetCamera(camera);
	//}

	if(testChara.GetComponent<CCameraComponent>(buf))
	{
		CCameraComponent& camera = dynamic_cast<CCameraComponent&>(*buf);
		this->RequestSetCamera(camera);
	}
	//if(testChara.GetAllComponents<CCameraComponent>(buf2))
	//{
	//	for(auto& buf : buf2)
	//	{
	//		buf->GetPriority();
	//	}
	//}
}