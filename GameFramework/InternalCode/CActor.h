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
	std::vector<std::unique_ptr<CComponent>> mComponents;		//コンポーネント
	CTransform mTransform;										//トランスフォーム
	ILevel& mOwnerInterface;									//インターフェース
public:
	CActor(CLevel& owner);

	//コンポーネント追加
	void AddComponent(CComponent& component)override;

	//更新
	void Update();

	//破壊
	void Destroy();
};