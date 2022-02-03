//!
//! @file
//! @brief ポインターアクターのソースファイル
//!

#include "GameFramework/Components/CBillboardComponent.h"
#include "GameFramework/Game/CApplication.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Game/CApplication.h"

#include "CFighter.h"
#include "CPointer.h"

CPointer::CPointer(ILevel& partner , CFighter& owner):CActor(partner) , mOwner(owner)
{
	//ディスプレイの中心座標取得
	int displayCenterPosX = GetSystemMetrics(SM_CXSCREEN) / 2;
	int displayCenterPosY = GetSystemMetrics(SM_CYSCREEN) / 2;

	//カーソルの座標をセット
	SetCursorPos(displayCenterPosX , displayCenterPosY);

	//マウスの初期座標初期化
	mInitMousePosX = CApplication::CLIENT_WIDTH / 2;
	mInitMousePosY = CApplication::CLIENT_HEIGHT / 2;

	//ビルボードコンポーネント追加&初期化
	CBillboardComponent& billboard = *new CBillboardComponent(*this , Transform , "Assets/Textures/Pointer/Pointer.png");
	billboard.Transform.Scale = { 10.0f,10.0f,1.0f };
}

void CPointer::Tick()
{
	//存在しなければ
	if(mInitLocation == nullptr)
	{
		//初期ロケーション作成&初期化
		mInitLocation.reset(new XMFLOAT3);
		*mInitLocation = mOwner.Transform.Location;
	}

	float mousePosX = CInputManager::GetInstance().GetMousePosX();
	float mousePosY = CInputManager::GetInstance().GetMousePosY();

	//差分座標算出
	mDiffPosX = mInitMousePosX - mousePosX;
	mDiffPosY = mInitMousePosY - mousePosY;

	//強弱の調整
	float posX , posY;
	posX = mDiffPosX / 6.f;
	posY = mDiffPosY / 6.f;

	//ロケーション更新
	Transform.Location.x = mInitLocation->x - posX;
	Transform.Location.y = mInitLocation->y + posY;
}