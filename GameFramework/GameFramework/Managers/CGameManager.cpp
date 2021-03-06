//!
//! @file
//! @brief ゲームマネージャーのソースファイル
//!

#include <Windows.h>

#include "../Game/CApplication.h"
#include "../Game/CGame.h"
#include "../Library/LCMath.h"

#include "CGameManager.h"

CGameManager::CGameManager():mGame(*this)
{
	mGameInterface = &mGame;
}

CGameManager& CGameManager::GetInstance()
{
	static CGameManager instance;

	return instance;
}

void CGameManager::RequestExecute(HINSTANCE hInst , int winMode)
{
	if(mCanExecute)
	{
		mCanExecute = false;

		mGameInterface->Execute(hInst , winMode);
	}
}

const XMFLOAT4X4* CGameManager::GetCameraViewMatrix()
{
	return mGame.GetLevel().GetRenderingCameraViewMatrix();
}

XMFLOAT3 CGameManager::GetCameraLocation()
{
	return mGame.GetLevel().GetRenderingCameraLocation();
}

float CGameManager::CalcDistanceToCamera(const XMFLOAT3& compareLocation)
{
	XMFLOAT3 cameraVec = mGame.GetLevel().GetRenderingCameraLocation();

	XMFLOAT3 calcVec = LCMath::CalcFloat3Subtraction(compareLocation , cameraVec);

	return LCMath::CalcFloat3Length(calcVec);
}
