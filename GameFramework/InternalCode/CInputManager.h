#pragma once
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>

enum class ButtonType
{
	KEYBOARD ,
	MOUSE ,
	X_CONTROLLER ,
};

struct SButtonInfo
{
	ButtonType ButtonType;
	int ButtonNum;

	SButtonInfo(int buttonNum = 0):ButtonNum(buttonNum)
	{}
};

struct SInputDefinition
{
	std::vector<SButtonInfo> ButtonInfoList;
	std::function<void()> ActionInfo;
};

class CInputManager
{
private:
	std::unordered_map<std::string , SInputDefinition> mActionList;

	CInputManager();

	CInputManager(const CInputManager&) = delete;
	CInputManager& operator=(const CInputManager&) = delete;
	CInputManager(CInputManager&&) = delete;
	CInputManager& operator=(CInputManager&&) = delete;
public:
	static CInputManager& GetInstance();

	//�A�N�V�����̃o�C���h�����N�G�X�g�@��actionName�̃L�[��mActionList�ɂȂ���΃G���[�\��
	void RequestBindAction(std::string actionName , std::function<void()>& func);

	//�A�N�V�����̒ǉ��@��actionName�̃L�[��mActionList�Ɋ��ɂ����Ă��㏑������
	void AddAction(std::string actionName , std::vector<SButtonInfo>& buttonInfoList , std::function<void()>& func);

	void Update();
};