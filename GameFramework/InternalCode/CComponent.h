#pragma once

class IActor;
class CActor;

class CComponent
{
private:
	int mPriority;					//優先度
	//IActor& mOwnerInterface;		//インターフェース
public:
	//★超重要★　コンストラクタを呼ぶということはアクターにコンポーネントを追加することを意味する
	CComponent(IActor& owner);
	virtual ~CComponent() = default;

	//更新
	virtual void Update() = 0;

	const int& GetPriority()const
	{
		return mPriority;
	}
};