#include <Windows.h>

#include "../Game/CApplication.h"
#include "../Game/CGame.h"

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
