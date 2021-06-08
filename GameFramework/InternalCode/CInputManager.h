#pragma once
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

enum class EButtonType
{
	NONE ,
	KEYBOARD ,
	MOUSE ,
	X_CONTROLLER ,
};

struct SButtonInfo
{
	EButtonType ButtonType = EButtonType::NONE;
	int ButtonNum = 0;
};

struct SInputDefinition
{
	std::vector<SButtonInfo> ButtonInfoList;
	std::function<void(void)> ActionInfo;
};

class CInputManager
{
public:

private:
	std::unordered_map<std::string , SInputDefinition> mActionList;		//�A�N�V�������X�g

	CInputManager();

	CInputManager(const CInputManager&) = delete;
	CInputManager& operator=(const CInputManager&) = delete;
	CInputManager(CInputManager&&) = delete;
	CInputManager& operator=(CInputManager&&) = delete;
public:
	static CInputManager& GetInstance();

	//�A�N�V�����̃o�C���h�����N�G�X�g�@��actionName�̃L�[��mActionList�ɂȂ���΃G���[�\��
	void RequestBindAction(std::string actionName , std::function<void(void)>& func);

	//�A�N�V�����̒ǉ��@��actionName�̃L�[��mActionList�Ɋ��ɂ����Ă��㏑������
	void AddAction(std::string actionName , std::vector<SButtonInfo> buttonInfoList , std::function<void(void)> func);
	void AddAction(std::string actionName , SButtonInfo buttonInfo , std::function<void(void)> func);

	//���͂���Ă��邩�̃`�F�b�N
	void CheckInput();
};