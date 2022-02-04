//!
//! @file
//! @brief 入力マネージャーのソースファイル
//!

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

void CInputManager::RequestBindEvent(std::string eventName , CObject& instancePtr , std::function<void()>& event)
{
	//指定のキーがなければエラー表示
	if(mInputEventList.count(eventName) == 0)
	{
		MessageBox(NULL , "RequestBindEvent Error:キーが見つかりません" , "Error" , MB_OK);
		return;
	}
	mInputEventList[eventName].InstancePointer = &instancePtr;
	mInputEventList[eventName].EventInfo = event;
}

void CInputManager::AddEvent(const std::string& eventName , const EButtonOption& buttonOption ,
	CObject& instancePtr , const std::vector<SButtonInfo>& buttonInfoList , const std::function<void()>& event)
{
	mInputEventList[eventName].ButtonOption = buttonOption;
	mInputEventList[eventName].InstancePointer = &instancePtr;
	mInputEventList[eventName].ButtonInfoList = buttonInfoList;
	mInputEventList[eventName].EventInfo = event;
}

void CInputManager::AddEvent(const std::string& eventName , const EButtonOption& buttonOption ,
	CObject& instancePtr , const SButtonInfo& buttonInfo , const std::function<void()>& event)
{
	mInputEventList[eventName].ButtonOption = buttonOption;
	mInputEventList[eventName].InstancePointer = &instancePtr;
	mInputEventList[eventName].ButtonInfoList.emplace_back(buttonInfo);
	mInputEventList[eventName].EventInfo = event;
}

void CInputManager::DeleteEvent(const std::string& eventName)
{
	//イベントを削除する関数オブジェクト作成
	auto deleteEvent = [& , eventName]
	{
		mInputEventList.erase(eventName);
	};

	mDeleteEvents.emplace_back(deleteEvent);
}

void CInputManager::ReleaseBind(CObject& target)
{
	//アクションリストが空だった場合終了
	if(mInputEventList.size() == 0)return;

	for(auto& event : mInputEventList)
	{
		if(event.second.InstancePointer == &target)
		{
			//バインドで実装することも鑑みて要素の削除(erase)ではなく値の代入で記述
			event.second.InstancePointer = nullptr;
			event.second.EventInfo = nullptr;
		}
	}
}

void CInputManager::CheckInput()
{
	CDirectInput& directInput = CDirectInput::GetInstance();
	CGameManager& gameManager = CGameManager::GetInstance();

	//DirectInputの更新
	directInput.GetKeyBuffer();
	directInput.GetMouseState();

	bool shouldEvent = false;

	//存在しなければ終了
	if(mInputEventList.size() == 0)return;

	if(mDeleteEvents.size() != 0)
	{
		for(auto& deleteEvent : mDeleteEvents)
		{
			deleteEvent();
		}

		//中身を空にする
		mDeleteEvents.clear();
		mDeleteEvents.shrink_to_fit();
	}

	for(auto& event : mInputEventList)
	{
		//イベント情報がなければcontinue
		if(event.second.EventInfo == nullptr)continue;

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
				MessageBox(NULL , "ボタンタイプがありません" , "Error" , MB_OK);
			}
			else if(buttonInfo.ButtonType == EButtonType::KEYBOARD)
			{
				if(event.second.ButtonOption == EButtonOption::NONE)
				{
					MessageBox(NULL , "ボタンオプションがありません" , "Error" , MB_OK);
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
					MessageBox(NULL , "ボタンオプションがありません" , "Error" , MB_OK);
				}
				else if(event.second.ButtonOption == EButtonOption::PRESS)
				{
					if(buttonInfo.ButtonNum == static_cast<int>(EMouseButtonType::NONE))
					{
						MessageBox(NULL , "ボタン番号がありません" , "Error" , MB_OK);
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
						MessageBox(NULL , "ボタン番号がありません" , "Error" , MB_OK);
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
						MessageBox(NULL , "ボタン番号がありません" , "Error" , MB_OK);
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

		//イベントを行うべきなら
		if(shouldEvent)
		{
			event.second.EventInfo();
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