#include <Windows.h>

#include "../ExternalCode/CDirectInput.h"
#include "../Actor/CActor.h"

#include "CInputManager.h"

CInputManager::CInputManager()
{
	//事前に作っておきたいアクションリストを書く
}

CInputManager& CInputManager::GetInstance()
{
	static CInputManager instance;

	return instance;
}

void CInputManager::RequestBindAction(std::string actionName , CActor& instancePtr , std::function<void()>& func)
{
	//指定のキーがなければエラー表示
	if(mActionList.count(actionName) == 0)
	{
		MessageBox(NULL , "RequestBindAction error:Not Found Key" , "error" , MB_OK);
		return;
	}
	mActionList[actionName].InstancePointer = &instancePtr;
	mActionList[actionName].ActionInfo = func;
}

void CInputManager::AddAction(const std::string& actionName , CActor& instancePtr , const std::vector<SButtonInfo>& buttonInfoList , const std::function<void()>& func)
{
	mActionList[actionName].InstancePointer = &instancePtr;
	mActionList[actionName].ButtonInfoList = buttonInfoList;
	mActionList[actionName].ActionInfo = func;
}

void CInputManager::AddAction(const std::string& actionName , CActor& instancePtr , const SButtonInfo& buttonInfo , const std::function<void()>& func)
{
	mActionList[actionName].InstancePointer = &instancePtr;
	mActionList[actionName].ButtonInfoList.emplace_back(buttonInfo);
	mActionList[actionName].ActionInfo = func;
}

void CInputManager::ReleaseBindTarget(CActor& target)
{
	//アクションリストが空だった場合終了
	if(!mActionList.size() > 0)return;

	for(auto& action : mActionList)
	{
		if(action.second.InstancePointer == &target)
		{
			//バインドで実装することも鑑みて要素の削除(erase)ではなく値の代入で記述
			action.second.InstancePointer = nullptr;
			action.second.ActionInfo = nullptr;
		}
	}
}

void CInputManager::CheckInput()
{
	CDirectInput::GetInstance().GetKeyBuffer();

	bool shouldAction = false;

	for(auto& action : mActionList)
	{
		for(auto& buttonInfo : action.second.ButtonInfoList)
		{
			//ボタンタイプ別の処理を記述
			switch(buttonInfo.ButtonType)
			{
			case EButtonType::KEYBOARD:
				if(CDirectInput::GetInstance().CheckKeyBuffer(buttonInfo.ButtonNum))
				{
					shouldAction = true;
					break;
				}
			}
		}
		if(shouldAction)
		{
			if(action.second.ActionInfo != nullptr)
			{
				action.second.ActionInfo();
			}
			else
			{
				MessageBox(NULL , "Not Found Function" , "error" , MB_OK);
			}
			shouldAction = false;
		}
	}
}