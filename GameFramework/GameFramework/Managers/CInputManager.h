//!
//! @file
//! @brief 入力マネージャーのヘッダーファイル
//!

#pragma once
#include <vector>
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include <dinput.h>

#include "../Object/CObject.h"

class CObject;

//! @brief ボタンタイプ列挙型
enum class EButtonType
{
	NONE ,				//!< NONE
	KEYBOARD ,			//!< キーボード
	MOUSE ,				//!< マウス
	X_CONTROLLER ,		//!< Xコントローラー
};

//! @brief ボタンオプション列挙型
enum class EButtonOption
{
	NONE ,				//!< NONE
	PRESS ,				//!< プレス
	TRIGGER ,			//!< トリガー
	RELEASE ,			//!< リリース
};

//! @brief マウスボタン列挙型
enum class EMouseButtonType
{
	NONE ,				//!< NONE
	L_BUTTON ,			//!< 左ボタン
	R_BUTTON ,			//!< 右ボタン
	C_BUTTON ,			//!< 中央ボタン
};

//! @brief ボタン情報構造体
struct SButtonInfo
{
	EButtonType ButtonType = EButtonType::NONE;			//!< ボタンタイプ
	int ButtonNum = 0;									//!< ボタン番号（ある場合）

	//!
	//! @brief コンストラクタ
	//! @param[in] type ボタンタイプ
	//! @param[in] buttonNum ボタン番号
	//!
	SButtonInfo(EButtonType type , int buttonNum = 0)
	{
		ButtonType = type;
		ButtonNum = buttonNum;
	}

	//!
	//! @brief コンストラクタ
	//! @param[in] mouseButtonNum ボタン番号
	//!
	SButtonInfo(EMouseButtonType mouseButtonNum)
	{
		ButtonType = EButtonType::MOUSE;
		ButtonNum = static_cast<int>(mouseButtonNum);
	}
};

//! @brief インプット定義構造体
struct SInputDefinition
{
	CObject* InstancePointer = nullptr;						//!< インスタンスのポインタ

	EButtonOption ButtonOption = EButtonOption::NONE;		//!< ボタンのオプション

	std::vector<SButtonInfo> ButtonInfoList;				//!< ボタンの情報リスト

	std::function<void()> EventInfo;						//!< 行いたいイベント情報
};

//! @brief 入力マネージャークラス
class CInputManager
{
private:
	std::unordered_map<std::string , SInputDefinition> mInputEventList;		//!< 入力イベントリスト

	//!
	//! @brief コンストラクタ
	//! @details 事前に入力イベントリストを作っておきたい場合はコンストラクタ内に書く
	//!
	CInputManager();

	//コピー＆ムーブ禁止
	CInputManager(const CInputManager&) = delete;
	CInputManager& operator=(const CInputManager&) = delete;
	CInputManager(CInputManager&&) = delete;
	CInputManager& operator=(CInputManager&&) = delete;

public:
	//!
	//! @brief インスタンス取得
	//! @return CInputManager& インスタンス
	//!
	static CInputManager& GetInstance();

	//!
	//! @brief イベントのバインドをリクエスト
	//! @details 作成済みの入力イベントリストにイベントをバインド（登録）したい際に利用する
	//! @param[in] eventName イベント名（入力イベントリストのキー）
	//! @param[in] instancePtr インスタンスポインタ
	//! @param[in] event バインドするイベント
	//!
	void RequestBindEvent(std::string eventName , CObject& instancePtr , std::function<void()>& event);

	//!
	//! @brief イベントの追加
	//! @details 作成済みの入力イベントリストがあれば上書きされる
	//! @param[in] eventName イベント名（入力イベントリストのキー）
	//! @param[in] buttonOption ボタンオプション
	//! @param[in] instancePtr インスタンスポインタ
	//! @param[in] buttonInfo 紐付けるボタン
	//! @param[in] event バインドするイベント
	//!
	void AddEvent(const std::string& eventName , const EButtonOption& buttonOption ,
		CObject& instancePtr , const SButtonInfo& buttonInfo , const std::function<void()>& event);

	//!
	//! @brief イベントの追加
	//! @details 作成済みの入力イベントリストがあれば上書きされる
	//! @param[in] eventName イベント名（入力イベントリストのキー）
	//! @param[in] buttonOption ボタンオプション
	//! @param[in] instancePtr インスタンスポインタ
	//! @param[in] buttonInfoList 紐付けるボタンのリスト
	//! @param[in] event バインドするイベント
	//!
	void AddEvent(const std::string& eventName , const EButtonOption& buttonOption ,
		CObject& instancePtr , const std::vector<SButtonInfo>& buttonInfoList , const std::function<void()>& event);

	//!
	//! @brief イベントの削除
	//! @param[in] eventName イベント名（入力イベントリストのキー）
	//!
	void DeleteEvent(const std::string& eventName);

	//!
	//! @brief バインドの解放
	//! @param[in] target バインドを解放したいオブジェクト
	//!
	void ReleaseBind(CObject& target);

	//! @brief 入力されているかのチェック
	void CheckInput();

	//! @brief マウスのX座標取得
	int GetMousePosX();

	//! @brief マウスのY座標取得
	int GetMousePosY();
};