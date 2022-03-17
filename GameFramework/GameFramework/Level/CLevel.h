//!
//!	@file
//!	@brief レベルシステムのヘッダーファイル
//!

#pragma once
#include <vector>
#include <memory>
#include <functional>

#include "../Object/CObject.h"
#include "../Actor/CActor.h"
#include "../Interfaces/IRender.h"

class IGame;
class IRender;
class CGame;
class CLevel;
class CGameManager;
class IGameManagerToLevel;
class CCameraComponent;

//! @brief 一般用レベルインターフェースクラス
class ILevel
{
public:
	//! @brief デストラクタ
	virtual ~ILevel() {};

	//!
	//! @brief アクターの追加
	//! @param[in] actor 追加するアクター
	//!
	virtual void AddActor(CActor& actor) = 0;

	//!
	//! @brief アクターのデストロイ
	//! @param[in] target デストロイするアクター
	//!
	virtual void DestroyActor(CActor& target) = 0;

	//!
	//! @brief ImGuiの描画イベントの追加
	//! @param[in] event 追加するImGuiの描画イベント
	//!
	virtual void AddImGuiDrawEvent(std::function<void()> event) = 0;

	//!
	//! @brief 更新前に行うイベントの追加
	//! @param[in] event 追加する更新前に行うイベント
	//!
	virtual void AddDoBeforeUpdateEvent(std::function<void()> event) = 0;

	//!
	//! @brief 描画カメラのセット
	//! @param[in] camera セットする描画カメラ
	//!
	virtual void SetRenderCamera(CCameraComponent& camera) = 0;

	//!
	//! @brief 描画命令の登録
	//! @param[in] renderOrders 登録する描画命令の配列
	//!
	virtual void RegisterRenderOrders(std::vector<SRenderInfo>& renderOrders) = 0;

	//!
	//! @brief レベルに通知
	//! @param[in] actor 通知元のアクター
	//!
	virtual void Notice(CActor& actor) = 0;
};

//! @briefレベルクラス
class CLevel :public CObject , public ILevel
{
private:
	std::vector<std::unique_ptr<CActor>> mActors;									//!< アクター

	std::vector<std::function<void()>> mDoBeforeUpdateEvents;						//!< 更新前に行うイベント
	std::vector<std::function<void()>> mDestroyEvents;								//!< デストロイのイベント
	std::vector<std::function<void()>> mImGuiDrawEvents;							//!< ImGuiに行わせる描画のイベント

	std::vector<IRender*> m3DOpaqueRenderComponents;								//!< 不透明3Dレンダーコンポーネント
	std::vector<std::pair<IRender* , float>> m3DTranslucentRenderComponents;		//!< 半透明3Dレンダーコンポーネント
	std::vector<IRender*> m2DOpaqueRenderComponents;								//!< 不透明2Dレンダーコンポーネント
	std::vector<IRender*> m2DTranslucentRenderComponents;							//!< 半透明2Dレンダーコンポーネント

	CCameraComponent* mRenderingCamera = nullptr;									//!< 描画を担当するカメラ

protected:
	IGame& mOwnerInterface;			//!< ゲームインターフェース

private:
	//コピー禁止
	CLevel(const CLevel&) = delete;
	CLevel& operator=(const CLevel&) = delete;

	//!
	//! @brief アクターの追加
	//! param[in] actor 追加するアクター
	//!
	void AddActor(CActor& actor)override;

	//!
	//! @brief アクターのデストロイ
	//! @param[in] target デストロイするアクター
	//!
	void DestroyActor(CActor& target)override;

	//!
	//! @brief 不透明3Dレンダーコンポーネントの追加
	//! @param[in] renderComponent 追加するレンダーコンポーネント
	//!
	void Add3DOpaqueRenderComponent(IRender& renderComponent)
	{
		m3DOpaqueRenderComponents.emplace_back(&renderComponent);
	}

	//!
	//! @brief 半透明3Dレンダーコンポーネントの追加
	//! @param[in] renderComponent 追加するレンダーコンポーネント
	//! @param[in] distanceToCamera カメラとの距離（描画順のソートのためのパラメータ）
	//!
	void Add3DTranslucentRenderComponent(IRender& renderComponent , float distanceToCamera)
	{
		m3DTranslucentRenderComponents.emplace_back(&renderComponent , distanceToCamera);
	}

	//!
	//! @brief 不透明2Dレンダーコンポーネントの追加
	//! @param[in] renderComponent 追加するレンダーコンポーネント
	//!
	void Add2DOpaqueRenderComponent(IRender& renderComponent)
	{
		m2DOpaqueRenderComponents.emplace_back(&renderComponent);
	}

	//!
	//! @brief 半透明2Dレンダーコンポーネントの追加
	//! @param[in] renderComponent 追加するレンダーコンポーネント
	//!
	void Add2DTranslucentRenderComponent(IRender& renderComponent)
	{
		m2DTranslucentRenderComponents.emplace_back(&renderComponent);
	}

	//!
	//! @brief 更新前に行うイベントの追加
	//! @param[in] event 追加する更新前に行うイベント
	//!
	void AddDoBeforeUpdateEvent(std::function<void()> event)override
	{
		mDoBeforeUpdateEvents.emplace_back(event);
	}

	//!
	//! @brief 描画命令の登録
	//! @param[in] renderOrders 登録する描画命令の配列
	//!
	void RegisterRenderOrders(std::vector<SRenderInfo>& renderOrders)override;

	//!
	//! @brief レベルに通知
	//! @param[in] actor 通知元のアクター
	//!
	virtual void Notice(CActor& actor)override {};

protected:
	//!
	//! @brief 描画カメラのセット
	//! @param[in] camera セットする描画カメラ
	//!
	void SetRenderCamera(CCameraComponent& camera)override;

	//!
	//! @brief ImGuiの描画イベントの追加
	//! @param[in] event 追加するImGuiの描画イベント
	//!
	void AddImGuiDrawEvent(std::function<void()> event)override
	{
		mImGuiDrawEvents.emplace_back(event);
	}

	//!
	//! @brief アクターの取得
	//! @param[out] result 取得した結果のアクター
	//! @return bool 取得が成功したか
	//!
	template<class T>
	bool GetActor(CActor*& result)
	{
		for(auto& actor : mActors)
		{
			//IDが一致するなら
			if(typeid(T) == typeid(*actor))
			{
				result = actor.get();
				return true;
			}
		}
		return false;
	}

	//!
	//! @brief アクターの全取得
	//! @param[out] result 取得した結果のアクター配列
	//! @return bool 取得が成功したか（1アクター以上取得出来た場合成功）
	//!
	template<class T>
	bool GetAllActor(std::vector<CActor*>& result)
	{
		for(auto& actor : mActors)
		{
			//IDが一致するなら
			if(typeid(T) == typeid(*actor))
			{
				result.emplace_back(actor.get());
			}
		}
		if(result.size() != 0)return true;
		else return false;
	}

public:
	//!
	//! @brief コンストラクタ
	//! @param[in] owner このレベルを所有するゲームシステム
	//! @param[in] isFeed フェードするか(フェードアウト)
	//! @param[in] feedColor フェード時の色情報
	//! @param[in] feedTime フェードにかかる秒数
	//!
	CLevel(IGame& owner , bool isFeed = false , XMFLOAT3 feedColor = { 1.0f,1.0f,1.0f } , float feedTime = 1.0f);

	//! @brief デストラクタ
	virtual ~CLevel();

	//!
	//! @brief 初期化
	//! @details 子クラスがこのメソッドをオーバーライドして独自の初期化を書き込む
	//!
	virtual void Init() = 0;

	//! @brief 更新
	void Update()override final;

	//!
	//! @brief ティック（毎フレーム行う追加処理）
	//! @details 子クラスがこのメソッドをオーバーライドして独自のティックを書き込む
	//!
	virtual void Tick() {};

	//! @brief 描画
	void Render()override;

	//!
	//! @brief 描画担当のカメラのビュー行列を取得
	//! @return const XMFLOAT4X4* 取得したビュー行列 ※nullptrなら失敗
	//!
	const XMFLOAT4X4* GetRenderingCameraViewMatrix()const;

	//!
	//! @brief 描画担当のカメラのロケーションを取得
	//! @return XMFLOAT3 取得したロケーション
	//!
	XMFLOAT3 GetRenderingCameraLocation()const;

};