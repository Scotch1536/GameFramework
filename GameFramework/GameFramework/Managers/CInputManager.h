#pragma once
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <dinput.h>

#include "../Object/CObject.h"

class CObject;

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

enum class EMouseButtonType
{
	NONE ,
	L_BUTTON ,
	R_BUTTON ,
	C_BUTTON ,
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
	SButtonInfo(EButtonType type , EMouseButtonType mouseButtonNum)
	{
		ButtonType = type;
		ButtonNum = static_cast<int>(mouseButtonNum);
	}
};

//インプット定義構造体
struct SInputDefinition
{
	CObject* InstancePointer = nullptr;			//インスタンスのポインタ

	EButtonOption ButtonOption = EButtonOption::NONE;		//ボタンのオプション

	std::vector<SButtonInfo> ButtonInfoList;				//ボタンの情報リスト

	std::function<void()> EventInfo;						//行いたいイベント
};

//インプットマネージャークラス：シングルトン
class CInputManager
{
private:
	std::unordered_map<std::string , SInputDefinition> mEventList;		//イベントリスト

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
	void RequestBindEvent(std::string actionName , CObject& instancePtr , std::function<void()>& event);

	//アクションの追加　※actionNameのキーがmActionListに既にあっても上書きする
	void AddEvent(const std::string& actionName , const EButtonOption& buttonOption ,
		CObject& instancePtr , const std::vector<SButtonInfo>& buttonInfoList , const std::function<void()>& event);

	void AddEvent(const std::string& actionName , const EButtonOption& buttonOption ,
		CObject& instancePtr , const SButtonInfo& buttonInfo , const std::function<void()>& event);

	//アクションの削除
	void DeleteEvent(const std::string& actionName);

	//指定のターゲットのバインドを解除
	void ReleaseBindTarget(CObject& target);

	//入力されているかのチェック
	void CheckInput();

	//マウスのポジションを取得(CheckInputの後に呼び出すことが前提)
	int GetMousePosX();
	int GetMousePosY();
};