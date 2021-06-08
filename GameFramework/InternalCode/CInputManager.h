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
	std::unordered_map<std::string , SInputDefinition> mActionList;		//アクションリスト

	CInputManager();

	CInputManager(const CInputManager&) = delete;
	CInputManager& operator=(const CInputManager&) = delete;
	CInputManager(CInputManager&&) = delete;
	CInputManager& operator=(CInputManager&&) = delete;
public:
	static CInputManager& GetInstance();

	//アクションのバインドをリクエスト　※actionNameのキーがmActionListになければエラー表示
	void RequestBindAction(std::string actionName , std::function<void(void)>& func);

	//アクションの追加　※actionNameのキーがmActionListに既にあっても上書きする
	void AddAction(std::string actionName , std::vector<SButtonInfo> buttonInfoList , std::function<void(void)> func);
	void AddAction(std::string actionName , SButtonInfo buttonInfo , std::function<void(void)> func);

	//入力されているかのチェック
	void CheckInput();
};