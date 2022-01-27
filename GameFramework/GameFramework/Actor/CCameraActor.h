//!
//! @file
//! @brief カメラアクターのヘッダーファイル
//!

#pragma once
#include "../Components/CCameraComponent.h"
#include "../Game/CApplication.h"

#include "CActor.h"

//! @brief カメラアクタークラス
class CCameraActor :public CActor
{
public:
	CCameraComponent& mCamera;		//!< カメラコンポーネント（利便性を重視しパブリック設定）

	//!
	//! @brief コンストラクタ
	//! @param[in] partner このアクターを所有するレベル
	//!
	CCameraActor(ILevel& partner):CActor(partner) , mCamera(*new CCameraComponent(*this))
	{
		mCamera.SetProjection(10.f , 10000.f , XM_PI / 4.f , CApplication::CLIENT_WIDTH , CApplication::CLIENT_HEIGHT);
		mCamera.SetView({ 0.0f,0.0f,0.0f } , { 0.0f,0.0f,1.0f } , { 0.0f,1.0f,0.0f });
	}
};