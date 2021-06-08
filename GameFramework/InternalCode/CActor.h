#pragma once
#include <vector>
#include <memory>

#include "CComponent.h"
#include "CTransform.h"
#include "IRender.h"

class CLevel;
class ILevel;

//インターフェース
class IActor
{
public:
	virtual ~IActor() {};
	virtual void AddComponent(CComponent& component) = 0;
	virtual void RegisterRenderComponent(IRender& component) = 0;
};

//アクタークラス
class CActor :public IActor , public IRender
{
private:
	//フレンド指定
	friend CComponent::CComponent(IActor&);

	std::vector<std::unique_ptr<CComponent>> mComponents;		//コンポーネント
	ILevel& mOwnerInterface;									//インターフェース
	std::vector<IRender*> mRenderAttributeComponents;			//描画の属性をもつコンポーネント

	//コピー禁止
	CActor(const CActor&) = delete;
	CActor& operator=(const CActor&) = delete;

	/*コンポーネント追加
	★超重要★子クラスは呼ぶことはできない
	コンポーネントのコンストラクタを呼ぶことでアクターの参照から辿ってこのメソッドが呼ばれる
	*/
	void AddComponent(CComponent& component)override;
	void RegisterRenderComponent(IRender& component)override;
protected:
	CTransform mTransform;										//トランスフォーム

public:
	//★超重要★　アクターのコンストラクタを呼ぶことはレベルにアクターを追加することを意味する
	CActor(CLevel& owner);

	virtual ~CActor() {};

	/*更新
	★超重要★このメソッドをオーバーライドする場合は必ず最後に親のメソッドを呼ぶこと
	*/
	virtual void Update();

	//描画
	void Render()override;

	//破壊
	void Destroy();

	//コンポーネントの属性から指定のコンポーネントをゲット
	bool GetComponentFromAttribute(CComponent::EAttribute attribute , CComponent*& inOut)const;
};