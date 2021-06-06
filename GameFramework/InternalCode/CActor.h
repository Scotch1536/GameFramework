#pragma once
#include <vector>
#include <memory>

#include "CComponent.h"
#include "CTransform.h"

class ILevel;
class CLevel;

//インターフェース
class IActor
{
public:
	virtual ~IActor() {};
	virtual void AddComponent(CComponent& component) = 0;
};

class CActor :public IActor
{
private:
	//コンポーネント追加　★超重要★子クラスは呼ぶことはできない
	void AddComponent(CComponent& component)override;
protected:
	std::vector<std::unique_ptr<CComponent>> mComponents;		//コンポーネント
	CTransform mTransform;										//トランスフォーム
	ILevel& mOwnerInterface;									//インターフェース
public:
	CActor(CLevel& owner);
	virtual ~CActor() = default;

	//更新
	void Update();

	//破壊
	void Destroy();
};