#include <Windows.h>

#include "../Game/Application.h"
#include "../Game/CGame.h"

#include "CGameManager.h"

CGameManager::CGameManager()
{
	mGame.reset(new CGame(*this));
}

CGameManager& CGameManager::GetInstance()
{
	static CGameManager instance;

	return instance;
}

void CGameManager::SetStartLevel(CLevel& startLevel)
{
	if(mCanSetStartLevel)
	{
		mCanSetStartLevel = false;

		static_cast<IGameToGameManager&>(*mGame).SetLevel(startLevel);
		startLevel.SetOwnerInterface(*mGame);
	}
	else
	{
		MessageBox(NULL , "Already SetStartLevel" , "error" , MB_OK);
		exit(1);
	}
}

void CGameManager::RequestExecute(HINSTANCE hInst , int winMode)
{
	if(mCanExecute)
	{
		mCanExecute = false;

		static_cast<IGameToGameManager&>(*mGame).Execute(hInst , winMode);
	}
	else
	{
		MessageBox(NULL , "Not Execute" , "error" , MB_OK);
	}
}

CGame& CGameManager::GetGame(Application& partner)
{
	return *mGame;
}

//IGame& CGameManager::GetGameInterface()
//{
//	return dynamic_cast<IGame&>(*mGame);
//}