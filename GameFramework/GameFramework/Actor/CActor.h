#pragma once
#include <vector>
#include <memory>

#include "../Components/CComponent.h"
#include "../Transform/CTransform.h"
#include "../Interfaces/IRender.h"

class ILevel;
class CTransform;

//インターフェース
class IActor
{
public:
	virtual ~IActor() {};
	virtual void AddComponent(CComponent& component) = 0;
	virtual void RegisterRenderComponent(IRender& component) = 0;
	virtual CTransform& GetTransform() = 0;
};

//アクタークラス
class CActor :public IActor
{
private:
	std::vector<std::unique_ptr<CComponent>> mComponents;		//コンポーネント
	std::vector<IRender*> mRenderAttributeComponents;			//描画の属性をもつコンポーネント

	ILevel& mOwnerInterface;		//インターフェース

	//コピー禁止
	CActor(const CActor&) = delete;
	CActor& operator=(const CActor&) = delete;

	/*コンポーネント追加
	★超重要★子クラスは呼ぶことはできない
	コンポーネントのコンストラクタを呼ぶことでアクターの参照から辿ってこのメソッドが呼ばれる
	*/
	void AddComponent(CComponent& component)override;

	//レンダー機能を持つコンポーネントを登録
	void RegisterRenderComponent(IRender& component)override;

	//トランスフォーム取得
	CTransform& GetTransform() override
	{
		return Transform;
	}
public:
	CTransform Transform;			//トランスフォーム

	//★超重要★　アクターのコンストラクタを呼ぶことはレベルにアクターを追加することを意味する
	CActor(ILevel& owner);

	virtual ~CActor();

	/*更新
	★超重要★このメソッドをオーバーライドする場合は必ず最後に親のメソッドを呼ぶこと
	*/
	void Update();

	//毎フレーム行う処理（子クラスのための機能）
	virtual void Tick() {};

	//描画
	void Render();

	//破壊
	void Destroy();

	//コンポーネントの属性から指定のコンポーネントをゲット
	bool GetComponentFromAttribute(CComponent::EAttribute attribute , CComponent*& result)const;

};