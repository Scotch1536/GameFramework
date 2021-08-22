#pragma once
#include <vector>
#include <memory>
#include <string>

#include "../Object/CObject.h"
#include "../Components/CComponent.h"
#include "../Transform/CTransform.h"
#include "../Interfaces/IRender.h"

class ILevel;
class CTransform;

//インターフェース
class IActor
{
public:
	virtual CActor& GetActor() = 0;
	virtual ~IActor() {};
};

class IActorToComponent :public IActor
{
public:
	virtual ~IActorToComponent() {};
	virtual void AddComponent(CComponent& component) = 0;
	virtual void AddRenderComponent(IRender& component) = 0;
	virtual CTransform& GetTransform() = 0;
	virtual void RequestAddAlphaRenderComponentToLevel(IRender& renderTarget , bool isFront = false) = 0;
	virtual void RequestAdd2DRenderComponentToLevel(IRender& renderTarget) = 0;
	virtual void RequestAddDoAfterUpdateFunction(const std::function<void()>& func) = 0;
};

//アクタークラス
class CActor :public CObject , public IActorToComponent
{
private:
	std::vector<std::unique_ptr<CComponent>> mComponents;		//コンポーネント
	std::vector<std::function<void()>> mDoAfterUpdateFunction;		//更新後に行う関数オブジェクト
	std::vector<IRender*> mRenderComponents;					//描画の属性をもつコンポーネント
	std::vector<std::string> mActorTags;						//タグ

	//コピー禁止
	CActor(const CActor&) = delete;
	CActor& operator=(const CActor&) = delete;

	/*コンポーネント追加
	★超重要★子クラスは呼ぶことはできない
	コンポーネントのコンストラクタを呼ぶことでアクターの参照から辿ってこのメソッドが呼ばれる
	*/
	void AddComponent(CComponent& component)override;

	void AddDoAfterUpdateFunction(const std::function<void()>& func)
	{
		mDoAfterUpdateFunction.emplace_back(func);
	}

	//レンダー機能を持つコンポーネントを登録
	void AddRenderComponent(IRender& component)override;

	void RequestAddAlphaRenderComponentToLevel(IRender& renderTarget , bool isFront)override;

	void RequestAdd2DRenderComponentToLevel(IRender& renderTarget)override;
	void RequestAddDoAfterUpdateFunction(const std::function<void()>& func)override;

	//アクター情報取得
	CActor& GetActor()override
	{
		return *this;
	}

	//トランスフォーム取得
	CTransform& GetTransform()override
	{
		return Transform;
	}

protected:
	ILevel& mOwnerInterface;		//インターフェース

	bool mIsAffectToPause;			//ポーズの影響を受けるかどうか

public:
	CTransform Transform;			//トランスフォーム

	//★超重要★　アクターのコンストラクタを呼ぶことはレベルにアクターを追加することを意味する
	CActor(ILevel& owner , bool isAffectToPause = true);

	virtual ~CActor();

	/*更新
	★超重要★このメソッドをオーバーライドする場合は必ず最後に親のメソッドを呼ぶこと
	*/
	void Update()override;

	//毎フレーム行う処理（子クラスのための機能）
	virtual void Tick() {};

	//描画
	void Render()override;

	//破壊
	void Destroy();

	//衝突開始時のイベント
	virtual void EventAtBeginCollide(CActor& collideActor) {};

	//衝突終了時のイベント
	virtual void EventAtEndCollide(CActor& collideActor) {};

	void AddTag(std::string tag)
	{
		mActorTags.emplace_back(tag);
	}

	bool HasTag(std::string tag)
	{
		for(auto& actorTag : mActorTags)
		{
			if(actorTag == tag)return true;
		}
		return false;
	}

	template<class T>
	bool GetComponent(CComponent*& result)
	{
		for(auto& component : mComponents)
		{
			if(typeid(T) == typeid(*component))
			{
				result = component.get();
				return true;
			}
		}
		return false;
	}

	template<class T>
	bool GetAllComponents(std::vector<CComponent*>& result)
	{
		for(auto& component : mComponents)
		{
			if(typeid(T) == typeid(*component))
			{
				result.emplace_back(component.get());
			}
		}
		if(result.size() != 0)return true;
		else return false;
	}

	void SetIsAffectToPause(bool flg)
	{
		mIsAffectToPause = flg;
	}

	const bool& GetIsAffectToPause()const
	{
		return mIsAffectToPause;
	}
};