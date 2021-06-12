#pragma once
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <dinput.h>

class CActor;

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
};

//�C���v�b�g��`�\����
struct SInputDefinition
{
	EButtonOption ButtonOption = EButtonOption::NONE;		//�{�^���̃I�v�V����
	CActor* InstancePointer = nullptr;						//�C���X�^���X�̃|�C���^
	std::vector<SButtonInfo> ButtonInfoList;				//�{�^���̏�񃊃X�g
	std::function<void()> ActionInfo;						//�s���������\�b�h�i�֐��j
};

//�C���v�b�g�}�l�[�W���[�N���X�F�V���O���g��
class CInputManager
{
private:
	std::unordered_map<std::string , SInputDefinition> mActionList;		//�A�N�V�������X�g

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
	void RequestBindAction(std::string actionName , CActor& instancePtr , std::function<void()>& func);

	//�A�N�V�����̒ǉ��@��actionName�̃L�[��mActionList�Ɋ��ɂ����Ă��㏑������
	void AddAction(const std::string& actionName , const EButtonOption& buttonOption ,
		CActor& instancePtr , const std::vector<SButtonInfo>& buttonInfoList , const std::function<void()>& func);

	void AddAction(const std::string& actionName , const EButtonOption& buttonOption ,
		CActor& instancePtr , const SButtonInfo& buttonInfo , const std::function<void()>& func);

	//�w��̃^�[�Q�b�g�̃o�C���h������
	void ReleaseBindTarget(CActor& target);

	//���͂���Ă��邩�̃`�F�b�N
	void CheckInput();
};