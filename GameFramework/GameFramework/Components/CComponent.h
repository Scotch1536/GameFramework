#pragma once

//!
//! @file
//! @brief コンポーネントのヘッダーファイル
//!

class IActorToComponent;
class CActor;

//! @brief コンポーネントクラス
class CComponent
{
private:
	int mPriority = 0;		//!< 優先度 0～100を想定

protected:
	IActorToComponent& mOwnerInterface;		//!< 所有者のインターフェース

	//コピー禁止
	CComponent(const CComponent&) = delete;
	CComponent& operator=(const CComponent&) = delete;

public:
	//!
	//! @brief コンストラクタ
	//! @details ★超重要★　コンストラクタを呼ぶことはアクターにコンポーネントを追加することを意味する
	//! @param[in] owner このコンポーネントの所有者
	//! @param[in] priority 優先度
	//!
	CComponent(CActor& owner , int priority = 100);

	//! @brief デストラクタ
	virtual ~CComponent() = 0;

	//! @brief 更新
	virtual void Update() {};

	//! @brief 所有者のアクター情報を取得
	//! @details 引数としての使用を想定しているのでそれ以外での使用は非推奨
	CActor& GetOwner()const;

	const int& GetPriority()const
	{
		return mPriority;
	}

};