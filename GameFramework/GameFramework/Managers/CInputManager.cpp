//!
//! @file
//! @brief ���̓}�l�[�W���[�̃\�[�X�t�@�C��
//!

#include <Windows.h>

#include "../ExternalCode/CDirectInput.h"
#include "../Managers/CGameManager.h"
#include "../Actor/CActor.h"

#include "CInputManager.h"

CInputManager::CInputManager()
{
	//���O�ɍ���Ă��������A�N�V�������X�g������
}

CInputManager& CInputManager::GetInstance()
{
	static CInputManager instance;

	return instance;
}

void CInputManager::RequestBindEvent(std::string eventName , CObject& instancePtr , std::function<void()>& event)
{
	//�w��̃L�[���Ȃ���΃G���[�\��
	if(mInputEventList.count(eventName) == 0)
	{
		MessageBox(NULL , "RequestBindEvent Error:�L�[��������܂���" , "Error" , MB_OK);
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
	mInputEventList.erase(eventName);
}

void CInputManager::ReleaseBind(CObject& target)
{
	//�A�N�V�������X�g���󂾂����ꍇ�I��
	if(mInputEventList.size() == 0)return;

	for(auto& action : mInputEventList)
	{
		if(action.second.InstancePointer == &target)
		{
			//�o�C���h�Ŏ������邱�Ƃ��ӂ݂ėv�f�̍폜(erase)�ł͂Ȃ��l�̑���ŋL�q
			action.second.InstancePointer = nullptr;
			action.second.EventInfo = nullptr;
		}
	}
}

void CInputManager::CheckInput()
{
	CDirectInput& directInput = CDirectInput::GetInstance();
	CGameManager& gameManager = CGameManager::GetInstance();

	//DirectInput�̍X�V
	directInput.GetKeyBuffer();
	directInput.GetMouseState();

	bool shouldEvent = false;

	for(auto& event : mInputEventList)
	{
		//�C�x���g��񂪂Ȃ����continue
		if(event.second.EventInfo == nullptr)continue;

		//�Q�[�����|�[�Y��Ԃ̏ꍇ���̃A�N�^�[���|�[�Y�̉e�����󂯂�Ȃ���͏������Ƃ΂�
		if(gameManager.GetIsPause())
		{
			if(event.second.InstancePointer->GetID() == "Actor")
			{
				if(dynamic_cast<CActor*>(event.second.InstancePointer)->GetIsAffectToPause())continue;
			}
		}

		for(auto& buttonInfo : event.second.ButtonInfoList)
		{
			//�{�^���^�C�v�ʂ̏������L�q
			if(buttonInfo.ButtonType == EButtonType::NONE)
			{
				MessageBox(NULL , "�{�^���^�C�v������܂���" , "Error" , MB_OK);
			}
			else if(buttonInfo.ButtonType == EButtonType::KEYBOARD)
			{
				if(event.second.ButtonOption == EButtonOption::NONE)
				{
					MessageBox(NULL , "�{�^���I�v�V����������܂���" , "Error" , MB_OK);
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
					MessageBox(NULL , "�{�^���I�v�V����������܂���" , "Error" , MB_OK);
				}
				else if(event.second.ButtonOption == EButtonOption::PRESS)
				{
					if(buttonInfo.ButtonNum == static_cast<int>(EMouseButtonType::NONE))
					{
						MessageBox(NULL , "�{�^���ԍ�������܂���" , "Error" , MB_OK);
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
						MessageBox(NULL , "�{�^���ԍ�������܂���" , "Error" , MB_OK);
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
						MessageBox(NULL , "�{�^���ԍ�������܂���" , "Error" , MB_OK);
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

		//�C�x���g���s���ׂ��Ȃ�
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