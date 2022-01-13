#pragma once
#include "../Components/CCameraComponent.h"
#include "../Game/CApplication.h"

#include "CActor.h"

//�J�����A�N�^�[
class CCameraActor :public CActor
{
public:
	CCameraComponent* mCamera = nullptr;		//�J�����R���|�[�l���g�i���֐����d�����p�u���b�N�ݒ�j

	CCameraActor(ILevel& partner):CActor(partner)
	{
		mCamera = new CCameraComponent(*this);
		mCamera->SetProjection(10.f , 10000.f , XM_PI / 4.f , CApplication::CLIENT_WIDTH , CApplication::CLIENT_HEIGHT);
		mCamera->SetView({ 0.0f,0.0f,0.0f } , { 0.0f,0.0f,1.0f } , { 0.0f,1.0f,0.0f });
	}
};