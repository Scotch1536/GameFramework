#pragma once
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <dinput.h>

#include "../Object/CObject.h"

class CObject;

//�{�^���^�C�v
enum class EButtonType
{
	NONE ,
	KEYBOARD ,
	MOUSE ,
	X_CONTROLLER ,
};

enum class EButtonOption
{
	NONE ,
	PRESS ,
	TRIGGER ,
	RELEASE ,
};

enum class EMouseButtonType
{
	NONE ,
	L_BUTTON ,
	R_BUTTON ,
	C_BUTTON ,
};

//�{�^�����\����
struct SButtonInfo
{
	EButtonType ButtonType = EButtonType::NONE;		//�{�^���^�C�v
	int ButtonNum = 0;								//�{�^���ԍ��i����ꍇ�j

	SButtonInfo(EButtonType type , int buttonNum = 0)
	{
		ButtonType = type;
		ButtonNum = buttonNum;
	}
	SButtonInfo(EButtonType type , EMouseButtonType mouseButtonNum)
	{
		ButtonType = type;
		ButtonNum = static_cast<int>(mouseButtonNum);
	}
};

//�C���v�b�g��`�\����
struct SInputDefinition
{
	CObject* InstancePointer = nullptr;			//�C���X�^���X�̃|�C���^

	EButtonOption ButtonOption = EButtonOption::NONE;		//�{�^���̃I�v�V����

	std::vector<SButtonInfo> ButtonInfoList;				//�{�^���̏�񃊃X�g

	std::function<void()> EventInfo;						//�s�������C�x���g
};

//�C���v�b�g�}�l�[�W���[�N���X�F�V���O���g��
class CInputManager
{
private:
	std::unordered_map<std::string , SInputDefinition> mEventList;		//�C�x���g���X�g

	//�����d�v���@���O�ɃA�N�V�������X�g������Ă��������ꍇ�̓R���X�g���N�^���ɏ���
	CInputManager();

	//�R�s�[�����[�u�֎~
	CInputManager(const CInputManager&) = delete;
	CInputManager& operator=(const CInputManager&) = delete;
	CInputManager(CInputManager&&) = delete;
	CInputManager& operator=(CInputManager&&) = delete;
public:
	static CInputManager& GetInstance();

	//�A�N�V�����̃o�C���h�����N�G�X�g�@��actionName�̃L�[��mActionList�ɂȂ���΃G���[�\��
	void RequestBindEvent(std::string actionName , CObject& instancePtr , std::function<void()>& event);

	//�A�N�V�����̒ǉ��@��actionName�̃L�[��mActionList�Ɋ��ɂ����Ă��㏑������
	void AddEvent(const std::string& actionName , const EButtonOption& buttonOption ,
		CObject& instancePtr , const std::vector<SButtonInfo>& buttonInfoList , const std::function<void()>& event);

	void AddEvent(const std::string& actionName , const EButtonOption& buttonOption ,
		CObject& instancePtr , const SButtonInfo& buttonInfo , const std::function<void()>& event);

	//�A�N�V�����̍폜
	void DeleteEvent(const std::string& actionName);

	//�w��̃^�[�Q�b�g�̃o�C���h������
	void ReleaseBindTarget(CObject& target);

	//���͂���Ă��邩�̃`�F�b�N
	void CheckInput();

	//�}�E�X�̃|�W�V�������擾(CheckInput�̌�ɌĂяo�����Ƃ��O��)
	int GetMousePosX();
	int GetMousePosY();
};