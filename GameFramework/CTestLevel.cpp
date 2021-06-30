#include <iostream>
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

	dice.Transform.Location = { 0.f,40.f,0.f };
	mEnemyTrans = &dice.Transform;
	/*
	レベルから指定のアクターインスタンスのメソッドをインプットマネージャーにバインドすることは可能
	アクターからでもレベルからでもどちらでも可能だ
	*/
	//CInputManager::GetInstance().AddAction("XP" , EButtonOption::PRESS , dice , { EButtonType::KEYBOARD,DIK_S } , std::bind(&CDice::Rot , std::ref(dice) , 0));

	CTestCharacter& testChara = *new CTestCharacter(*this);
	mPlayerTrans = &testChara.Transform;
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

	if (testChara.GetComponent<CCameraComponent>(buf))
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

void CTestLevel::Tick()
{
	if (mEnemyTrans != nullptr && mPlayerTrans != nullptr)
	{
		float xAns = mPlayerTrans->GetWorldMatrixResult()._41 - mEnemyTrans->GetWorldMatrixResult()._41;
		float yAns = mPlayerTrans->GetWorldMatrixResult()._42 - mEnemyTrans->GetWorldMatrixResult()._42;
		float zAns = mPlayerTrans->GetWorldMatrixResult()._43 - mEnemyTrans->GetWorldMatrixResult()._43;

		float dist = std::sqrt((xAns * xAns) + (yAns * yAns) + (zAns * zAns));
		//std::system("cls");
		//std::cout << "敵との距離：" << dist-26 <<std::endl;
	}
	else
	{
		std::system("cls");
		std::cout << "敵消滅" << std::endl;
	}
}