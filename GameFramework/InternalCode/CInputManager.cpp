#include <Windows.h>

#include "CInputManager.h"
#include "CDirectInput.h"
#include "Application.h"

CInputManager::CInputManager() {}

CInputManager& CInputManager::GetInstance()
{
	static CInputManager instance;

	return instance;
}

void CInputManager::RequestBindAction(std::string actionName , std::function<void()>& func)
{
	if(mActionList.count(actionName) == 0)
	{
		MessageBox(NULL , "RequestBindAction error:Not Found Key" , "error" , MB_OK);
		return;
	}
	mActionList[actionName].ActionInfo = func;
}

void CInputManager::AddAction(std::string actionName , std::vector<SButtonInfo>& buttonInfoList , std::function<void()>& func)
{
	mActionList[actionName].ButtonInfoList = buttonInfoList;
	mActionList[actionName].ActionInfo = func;
}

void CInputManager::Update()
{
	for(auto& action : mActionList)
	{
		bool shouldAction = false;
		for(auto& buttonInfo : action.second.ButtonInfoList)
		{
			switch(buttonInfo.ButtonType)
			{
			case ButtonType::KEYBOARD:
				if(CDirectInput::GetInstance().CheckKeyBuffer(buttonInfo.ButtonNum))
				{
					shouldAction = true;
					break;
				}
			}
		}
		if(shouldAction)
		{
			action.second.ActionInfo();
			shouldAction = false;
		}
	}
}