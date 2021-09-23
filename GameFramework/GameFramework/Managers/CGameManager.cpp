#include <Windows.h>

#include "../Game/CApplication.h"
#include "../Game/CGame.h"
#include "../Library/LCMath.h"

#include "CGameManager.h"

CGameManager::CGameManager():mGame(*this)
{}

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

		static_cast<IGameToGameManager&>(mGame).Execute(hInst , winMode);
	}
	else
	{
		MessageBox(NULL , "Not Execute" , "error" , MB_OK);
	}
}

const XMFLOAT4X4* CGameManager::GetCameraViewMatrix()
{
	return mGame.GetLevel().GetRenderingCameraViewMatrix();
}

const XMFLOAT3* CGameManager::GetCameraLocation()
{
	return mGame.GetLevel().GetRenderingCameraLocation();
}

float CGameManager::CalcDistanceToCamera(const XMFLOAT3& compareLocation)
{
	const XMFLOAT3* cameraVec = mGame.GetLevel().GetRenderingCameraLocation();

	if(cameraVec != nullptr)
	{
		XMFLOAT3 calcVec = LCMath::CalcFloat3FromStartToGoal(compareLocation , *cameraVec);

		return LCMath::CalcFloat3Length(calcVec);
	}
	else return 0.0f;
}
