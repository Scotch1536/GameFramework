#include <Windows.h>

#include "CGameManager.h"
#include "CGame.h"
#include "Application.h"

CGameManager::CGameManager()
{
	mGame.reset(new CGame());
}

CGameManager& CGameManager::GetInstance()
{
	static CGameManager instance;

	return instance;
}

//void CGameManager::SetStartLevel(CLevel* startLevel)
//{
//	if(mCanSetStartLevel)
//	{
//		mCanSetStartLevel = false;
//
//		mStartLevel.reset(startLevel);
//	}
//	else
//	{
//		MessageBox(NULL , "Already SetStartLevel" , "error" , MB_OK);
//	}
//}

template<class StartLevel>
void CGameManager::RequestExecute(HINSTANCE hInst , int winMode)
{
	if(mCanExecute)
	{
		mCanExecute = false;

		mGame->Execute<StartLevel>(hInst,winMode);
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

IGame& CGameManager::GetGameInterface()
{
	return dynamic_cast<IGame&>(*mGame);
}