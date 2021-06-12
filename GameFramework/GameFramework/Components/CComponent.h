#pragma once

class IActor;
class CActor;

//コンポーネントクラス
class CComponent
{
public:
	//属性構造体
	enum class EAttribute
	{
		NONE ,
		CAMERA ,
		RENDER ,
		LIGHT,
	};

private:
	int mPriority = 0;		//優先度 0～100を想定

protected:
	EAttribute mAttribute = EAttribute::NONE;		//属性

	IActor& mOwnerInterface;		//インターフェース

	//コピー禁止
	CComponent(const CComponent&) = delete;
	CComponent& operator=(const CComponent&) = delete;

public:
	//★超重要★　コンストラクタを呼ぶことはアクターにコンポーネントを追加することを意味する
	CComponent(CActor& owner , int priority);
	virtual ~CComponent() = 0;

	//更新
	virtual void Update() {};

	const int& GetPriority()const
	{
		return mPriority;
	}

	const EAttribute& GetAttribute()const
	{
		return mAttribute;
	}
};