#pragma once

class IActor;
class CActor;

//コンポーネントクラス
class CComponent
{
private:
	int mPriority = 0;		//優先度 0～100を想定

protected:
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

	CActor& GetOwner()const
	{
		return mOwnerInterface.GetActor();
	}
};