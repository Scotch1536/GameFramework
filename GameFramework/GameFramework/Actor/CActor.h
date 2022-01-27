//!
//! @file
//! @brief アクター関連のヘッダーファイル
//!

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

//! @brief レンダーオプション列挙型
enum class ERenderOption
{
	OPACITY3D ,				//!< 不透明3D
	TRANSLUCENT3D ,			//!< 半透明3D
	BILLBOARD ,				//!< ビルボード
	OPACITY2D ,				//!< 不透明2D
	TRANSLUCENT2D ,			//!< 半透明2D
};

//! @brief レンダー情報構造体
struct SRenderInfo
{
	IRender& RenderComponentReference;		//!< レンダーコンポーネントの参照
	ERenderOption RenderOption;				//!< レンダーオプション
	float DistanceToCamera = 0.0f;			//!< カメラとの距離
};

//!< @brief アクターインターフェースクラス
class IActor
{
public:
	virtual ~IActor() {};

	//!
	//! @brief アクターの取得
	//! @return CActor& アクター
	//!
	virtual CActor& GetActor() = 0;
};

//!< @brief コンポーネント用アクターインターフェースクラス
class IActorToComponent :public IActor
{
public:
	virtual ~IActorToComponent() {};

	//!
	//! @brief コンポーネント追加
	//! @param[in] component 追加するコンポーネント
	//!
	virtual void AddComponent(CComponent& component) = 0;

	//!
	//! @brief 描画命令追加
	//! @param[in] order 追加する描画命令
	//!
	virtual void AddRenderOrder(const SRenderInfo& order) = 0;

	//!
	//! @brief トランスフォーム取得
	//! @return CTransform& トランスフォーム
	//!
	virtual CTransform& GetTransform() = 0;

	//!
	//! @brief レベルの更新前実行関数に追加のリクエスト
	//! @param[in] func 追加する関数オブジェクト
	//!
	virtual void RequestAddDoBeforeUpdateFunction(std::function<void()> func) = 0;
};

//! @brief アクタークラス
class CActor :public CObject , public IActorToComponent
{
private:
	std::vector<std::unique_ptr<CComponent>> mComponents;		//!< コンポーネント　※優先度の昇順に整列される
	std::vector<SRenderInfo> mRenderOrders;						//!< 描画命令　※毎フレームリフレッシュされる
	std::vector<std::string> mTags;								//!< タグ

	//!
	//! @brief コンポーネント追加
	//! @details コンポーネント側から呼び出されるシステムになっている
	//! @param[in] component 追加するコンポーネント
	//!
	void AddComponent(CComponent& component)override;

	//!
	//! @brief コンポーネント追加
	//! @param[in] order 追加する描画命令
	//!
	void AddRenderOrder(const SRenderInfo& order)override;
  
	//!
	//! @brief レベルの更新前実行関数に追加のリクエスト
	//! @param[in] func 追加する関数オブジェクト
	//!
	void RequestAddDoBeforeUpdateFunction(std::function<void()> func)override;

	//!
	//! @brief アクターの取得
	//! @return CActor& アクター
	//!
	CActor& GetActor()override
	{
		return *this;
	}

	//!
	//! @brief トランスフォーム取得
	//! @return CTransform& トランスフォーム
	//!
	CTransform& GetTransform()override
	{
		return Transform;
	}


protected:
	ILevel& mOwnerInterface;		//!< 所有レベルのインターフェース

	bool mIsAffectToPause;			//!< ポーズの影響を受けるかどうか

public:
	CTransform Transform;			//!< トランスフォーム

	//!
	//! @brief コンストラクタ
	//! @details コンストラクタを呼ぶことはレベルにアクターを追加することを意味する
	//! @param[in] owner このアクターを所有するレベル
	//! @param[in] isAffectToPause ポーズの影響を受けるかどうか
	//!
	CActor(ILevel& owner , bool isAffectToPause = true);

	//! @brief デストラクタ
	virtual ~CActor();

	//! @brief 更新
	void Update()override final;

	//! @brief 描画
	void Render()override;

	//!
	//! @brief ティック（毎フレーム行う追加処理）
	//! @details 子クラスがオーバーライドして利用することを想定
	//!
	virtual void Tick() {};

	//! @brief 自身の破壊
	void Destroy();

	//!
	//! @brief 衝突開始時のイベント
	//! @details コライダーコンポーネントで扱うためのメソッドなのでそれ以外の用法は非推奨
	//! @param[in] collideActor 当たったアクター
	//!
	virtual void EventAtBeginCollide(CActor& collideActor) {};

	//!
	//! @brief 衝突終了時のイベント
	//! @details コライダーコンポーネントで扱うためのメソッドなのでそれ以外の用法は非推奨
	//! @param[in] collideActor 当たったアクター
	//!
	virtual void EventAtEndCollide(CActor& collideActor) {};

	//!
	//! @brief タグ追加
	//! @param[in] tag 追加したいタグ
	//!
	void AddTag(std::string tag)
	{
		mTags.emplace_back(tag);
	}

	//!
	//! @brief 引数のタグを所持しているかを検証
	//! @param[in] tag 所持を確認したいタグ
	//! @return bool 所持しているか
	//!
	bool HasTag(std::string tag)
	{
		for(auto& actorTag : mTags)
		{
			if(actorTag == tag)return true;
		}
		return false;
	}

	//!
	//! @brief コンポーネントを取得
	//! @details コンポーネントが見つかったらその時点で終了する
	//! @param[out] result 見つかったコンポーネント
	//! @return bool 見つかったかどうか
	//!
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

	//!
	//! @brief コンポーネントをすべて取得
	//! @param[out] result 見つかったコンポーネント
	//! @return bool 見つかったかどうか
	//!
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