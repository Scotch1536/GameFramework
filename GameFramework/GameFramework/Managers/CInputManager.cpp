#include <Windows.h>

#include "../ExternalCode/CDirectInput.h"
#include "../Managers/CGameManager.h"
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

void CInputManager::RequestBindEvent(std::string actionName , CObject& instancePtr , std::function<void()>& func)
{
	//指定のキーがなければエラー表示
	if(mEventList.count(actionName) == 0)
	{
		MessageBox(NULL , "RequestBindAction error:Not Found Key" , "error" , MB_OK);
		return;
	}
	mEventList[actionName].InstancePointer = &instancePtr;
	mEventList[actionName].EventInfo = func;
}

void CInputManager::AddEvent(const std::string& actionName , const EButtonOption& buttonOption ,
	CObject& instancePtr , const std::vector<SButtonInfo>& buttonInfoList , const std::function<void()>& func)
{
	mEventList[actionName].ButtonOption = buttonOption;
	mEventList[actionName].InstancePointer = &instancePtr;
	mEventList[actionName].ButtonInfoList = buttonInfoList;
	mEventList[actionName].EventInfo = func;
}

void CInputManager::AddEvent(const std::string& actionName , const EButtonOption& buttonOption ,
	CObject& instancePtr , const SButtonInfo& buttonInfo , const std::function<void()>& func)
{
	mEventList[actionName].ButtonOption = buttonOption;
	mEventList[actionName].InstancePointer = &instancePtr;
	mEventList[actionName].ButtonInfoList.emplace_back(buttonInfo);
	mEventList[actionName].EventInfo = func;
}

void CInputManager::ReleaseBindTarget(CObject& target)
{
	//アクションリストが空だった場合終了
	if(!(mEventList.size() > 0))return;

	for(auto& action : mEventList)
	{
		if(action.second.InstancePointer == &target)
		{
			//バインドで実装することも鑑みて要素の削除(erase)ではなく値の代入で記述
			action.second.InstancePointer = nullptr;
			action.second.EventInfo = nullptr;
		}
	}
}

void CInputManager::CheckInput()
{
	CDirectInput& directInput = CDirectInput::GetInstance();
	CGameManager& gameManager = CGameManager::GetInstance();

	directInput.GetKeyBuffer();
	directInput.GetMouseState();

	bool shouldEvent = false;

	for(auto& event : mEventList)
	{
		//ゲームがポーズ状態の場合そのアクターがポーズの影響を受けるなら入力処理をとばす
		if(gameManager.GetIsPause())
		{
			if(event.second.InstancePointer->GetID() == "Actor")
			{
				if(dynamic_cast<CActor*>(event.second.InstancePointer)->GetIsAffectToPause())continue;
			}
		}

		for(auto& buttonInfo : event.second.ButtonInfoList)
		{
			//ボタンタイプ別の処理を記述
			if(buttonInfo.ButtonType == EButtonType::NONE)
			{
				MessageBox(NULL , "ButtonType is NONE" , "error" , MB_OK);
			}
			else if(buttonInfo.ButtonType == EButtonType::KEYBOARD)
			{
				if(event.second.ButtonOption == EButtonOption::NONE)
				{
					MessageBox(NULL , "ButtonType is NONE" , "error" , MB_OK);
				}
				else if(event.second.ButtonOption == EButtonOption::PRESS)
				{
					if(directInput.CheckKeyBuffer(buttonInfo.ButtonNum))
					{
						shouldEvent = true;
						break;
					}
				}
				else if(event.second.ButtonOption == EButtonOption::TRIGGER)
				{
					if(directInput.CheckKeyBufferTrigger(buttonInfo.ButtonNum))
					{
						shouldEvent = true;
						break;
					}
				}
				else if(event.second.ButtonOption == EButtonOption::RELEASE)
				{
					if(directInput.CheckKeyBufferRelease(buttonInfo.ButtonNum))
					{
						shouldEvent = true;
						break;
					}
				}
			}
			else if(buttonInfo.ButtonType == EButtonType::MOUSE)
			{
				if(event.second.ButtonOption == EButtonOption::NONE)
				{
					MessageBox(NULL , "ButtonType is NONE" , "error" , MB_OK);
				}
				else if(event.second.ButtonOption == EButtonOption::PRESS)
				{
					if(buttonInfo.ButtonNum == static_cast<int>(EMouseButtonType::NONE))
					{
						MessageBox(NULL , "ButtonNum is NONE" , "error" , MB_OK);
					}
					else if(buttonInfo.ButtonNum == static_cast<int>(EMouseButtonType::L_BUTTON))
					{
						if(directInput.GetMouseLButtonCheck())
						{
							shouldEvent = true;
							break;
						}
					}
					else if(buttonInfo.ButtonNum == static_cast<int>(EMouseButtonType::R_BUTTON))
					{
						if(directInput.GetMouseRButtonCheck())
						{
							shouldEvent = true;
							break;
						}
					}
					else if(buttonInfo.ButtonNum == static_cast<int>(EMouseButtonType::C_BUTTON))
					{
						if(directInput.GetMouseCButtonCheck())
						{
							shouldEvent = true;
							break;
						}
					}
				}
				else if(event.second.ButtonOption == EButtonOption::TRIGGER)
				{
					if(buttonInfo.ButtonNum == static_cast<int>(EMouseButtonType::NONE))
					{
						MessageBox(NULL , "ButtonNum is NONE" , "error" , MB_OK);
					}
					else if(buttonInfo.ButtonNum == static_cast<int>(EMouseButtonType::L_BUTTON))
					{
						if(directInput.GetMouseLButtonTrigger())
						{
							shouldEvent = true;
							break;
						}
					}
					else if(buttonInfo.ButtonNum == static_cast<int>(EMouseButtonType::R_BUTTON))
					{
						if(directInput.GetMouseRButtonTrigger())
						{
							shouldEvent = true;
							break;
						}
					}
					else if(buttonInfo.ButtonNum == static_cast<int>(EMouseButtonType::C_BUTTON))
					{
						if(directInput.GetMouseCButtonTrigger())
						{
							shouldEvent = true;
							break;
						}
					}
				}
				else if(event.second.ButtonOption == EButtonOption::RELEASE)
				{
					if(buttonInfo.ButtonNum == static_cast<int>(EMouseButtonType::NONE))
					{
						MessageBox(NULL , "ButtonNum is NONE" , "error" , MB_OK);
					}
					else if(buttonInfo.ButtonNum == static_cast<int>(EMouseButtonType::L_BUTTON))
					{
						if(directInput.GetMouseLButtonRelease())
						{
							shouldEvent = true;
							break;
						}
					}
					else if(buttonInfo.ButtonNum == static_cast<int>(EMouseButtonType::R_BUTTON))
					{
						if(directInput.GetMouseRButtonRelease())
						{
							shouldEvent = true;
							break;
						}
					}
					else if(buttonInfo.ButtonNum == static_cast<int>(EMouseButtonType::C_BUTTON))
					{
						if(directInput.GetMouseCButtonRelease())
						{
							shouldEvent = true;
							break;
						}
					}
				}
			}
		}
		if(shouldEvent)
		{
			if(event.second.EventInfo != nullptr)
			{
				event.second.EventInfo();
			}
			shouldEvent = false;
		}
	}
}

int CInputManager::GetMousePosX()
{
	return CDirectInput::GetInstance().GetMousePosX();
}

int CInputManager::GetMousePosY()
{
	return CDirectInput::GetInstance().GetMousePosY();
}