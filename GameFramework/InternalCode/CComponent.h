#pragma once

class IActor;

//コンポーネントクラス
class CComponent
{
public:
	enum class EAttribute
	{
		NONE ,
		CAMERA ,
	};

	//enum class ComponentType
	//{
	//	NONE = 0b00 ,
	//	SMESH = 0b01 ,
	//};

protected:
	int mPriority = 0;		//優先度

	EAttribute mAttribute = EAttribute::NONE;
	//ComponentType mType = ComponentType::NONE;

	//コピー禁止
	CComponent(const CComponent&) = delete;
	CComponent& operator=(const CComponent&) = delete;

public:
	//★超重要★　コンストラクタを呼ぶことはアクターにコンポーネントを追加することを意味する
	CComponent(IActor& owner);
	virtual ~CComponent() = default;

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

	//const int& GetType()const
	//{
	//	return static_cast<int>(mType);
	//}
};