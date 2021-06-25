#pragma once
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <dinput.h>

#include "../Abstract/ACObject.h"

class ACObject;

//ボタンタイプ
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

//ボタン情報構造体
struct SButtonInfo
{
	EButtonType ButtonType = EButtonType::NONE;		//ボタンタイプ
	int ButtonNum = 0;								//ボタン番号（ある場合）

	SButtonInfo(EButtonType type , int buttonNum = 0)
	{
		ButtonType = type;
		ButtonNum = buttonNum;
	}
};

//インプット定義構造体
struct SInputDefinition
{
	ACObject* InstancePointer = nullptr;					//インスタンスのポインタ

	EButtonOption ButtonOption = EButtonOption::NONE;		//ボタンのオプション

	std::vector<SButtonInfo> ButtonInfoList;				//ボタンの情報リスト

	std::function<void()> ActionInfo;						//行いたいメソッド（関数）
};

//インプットマネージャークラス：シングルトン
class CInputManager
{
private:
	std::unordered_map<std::string , SInputDefinition> mActionList;		//アクションリスト

	//★超重要★　事前にアクションリストを作っておきたい場合はコンストラクタ内に書く
	CInputManager();

	//コピー＆ムーブ禁止
	CInputManager(const CInputManager&) = delete;
	CInputManager& operator=(const CInputManager&) = delete;
	CInputManager(CInputManager&&) = delete;
	CInputManager& operator=(CInputManager&&) = delete;
public:
	static CInputManager& GetInstance();

	//アクションのバインドをリクエスト　※actionNameのキーがmActionListになければエラー表示
	void RequestBindAction(std::string actionName , ACObject& instancePtr , std::function<void()>& func);

	//アクションの追加　※actionNameのキーがmActionListに既にあっても上書きする
	void AddAction(const std::string& actionName , const EButtonOption& buttonOption ,
		ACObject& instancePtr , const std::vector<SButtonInfo>& buttonInfoList , const std::function<void()>& func);

	void AddAction(const std::string& actionName , const EButtonOption& buttonOption ,
		ACObject& instancePtr , const SButtonInfo& buttonInfo , const std::function<void()>& func);

	//指定のターゲットのバインドを解除
	void ReleaseBindTarget(ACObject& target);

	//入力されているかのチェック
	void CheckInput();
};