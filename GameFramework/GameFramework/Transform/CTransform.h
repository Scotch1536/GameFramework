//!
//!	@file
//!	@brief トランスフォームシステムのヘッダーファイル
//!

#pragma once
#include <vector>
#include <memory>
#include <array>
#include <functional>
#include <DirectXMath.h>

#include "CRotator.h"

using namespace DirectX;

class CChildTransform;
class IActor;

//! @brief トランスフォームクラス
class CTransform final
{
public:
	//! @brief アタッチオプション列挙型
	enum class EAttachOption
	{
		DEFAULT = 0b00 ,			//!< デフォルト
		LOCATION_ONLY = 0b01 ,		//!< ロケーションのみ
	};

private:
	EAttachOption mAttachOption = EAttachOption::DEFAULT;			//!< アタッチオプション

	XMFLOAT4X4 mWorldMatrix;										//!< ワールド変換行列
	XMFLOAT4X4 mLocalMatrix;										//!< ローカル変換行列

	CTransform* mParentTransform = nullptr;							//!< 親トランスフォーム
	std::vector<CTransform*> mChildTransform;						//!< 子トランスフォーム

	XMFLOAT3 mLastFrameLocation = { 0.f,0.f,0.f };					//!< 前フレームのロケーション
	XMFLOAT3 mLastFrameScale = { 0.f,0.f,0.f };						//!< 前フレームのスケール

	IActor& mOwnerInterface;										//!< 自身を所有するアクターのインターフェース

	std::vector<std::function<void()>> mEventWhenMatrixUpdate;		//!< 行列更新時実行イベント

	bool mShouldUpdateMatrix = true;								//!< 行列を更新すべきか
	bool mIgnoreUpdateMatrixOnce = false;							//!< 一度行列の更新を無視するか
	bool mIsChild = false;											//!< 自分が子トランスフォームか
	bool mIsBillboard = false;										//!< ビルボードか
	bool mDoDrawDebugLine = false;									//!< デバッグラインを描画するか

	//!
	//! @brief ローカル変換行列をセット
	//! @param[in] matrix セットするワールド変換行列
	//!
	void SetLocalMatrix(const XMFLOAT4X4& matrix);
	
public:
	XMFLOAT3 Location = { 0.f,0.f,0.f };		//!< ロケーション
	XMFLOAT3 Scale = { 1.f,1.f,1.f };			//!< スケール

	CRotator Rotation;							//!< ローテーター

	//!
	//! @brief コンストラクタ
	//! @param[in] partner このトランスフォームを所有するアクター
	//!
	CTransform(IActor& partner);

	//!
	//! @brief コンストラクタ
	//! @details 作るときから従属するトランスフォームが決まっている際に利用する
	//! @param[in] partner このトランスフォームを所有するアクター
	//! @param[in] parentTrans 親のトランスフォーム
	//!
	CTransform(IActor& partner , CTransform& parentTrans);

	//! @brief デストラクタ
	~CTransform();

	//! @brief 更新
	void Update();

	//! @brief GPUに行列をセットするリクエスト
	void RequestSetMatrix();

	//!
	//! @brief トランスフォームをアタッチ
	//! @details 引数のトランスフォームが子トランスフォームとしてアタッチされる
	//! @param[in] attachTarget 自身にアタッチするトランスフォーム
	//!
	void AttachTransform(CTransform& attachTarget);

	//!
	//! @brief トランスフォームをデタッチ
	//! @details 引数のトランスフォームがデタッチされる
	//! @param[in] detachTarget 自身にデタッチするトランスフォーム
	//!
	void DetachTransform(CTransform& detachTarget);

	//! @brief デバッグライン機能をリクエスト
	void RequestDebugLine();

	//!
	//! @brief ワールドの右向きベクトル取得
	//! @return XMFLOAT3 ワールドの右向きベクトル
	//!
	XMFLOAT3 GetWorldRightVector()const;

	//!
	//! @brief ワールドの上向きベクトル取得
	//! @return XMFLOAT3 ワールドの上向きベクトル
	//!
	XMFLOAT3 GetWorldUpwardVector()const;

	//!
	//! @brief ワールドの前向きベクトル取得
	//! @return XMFLOAT3 ワールドの前向きベクトル
	//!
	XMFLOAT3 GetWorldForwardVector()const;
	
	//!
	//! @brief ローカルの右向きベクトル取得
	//! @return XMFLOAT3 ローカルの右向きベクトル
	//!
	XMFLOAT3 GetLocalRightVector()const;

	//!
	//! @brief ローカルの上向きベクトル取得
	//! @return XMFLOAT3 ローカルの上向きベクトル
	//!
	XMFLOAT3 GetLocalUpwardVector()const;

	//!
	//! @brief ローカルの前向きベクトル取得
	//! @return XMFLOAT3 ローカルの前向きベクトル
	//!
	XMFLOAT3 GetLocalForwardVector()const;

	//! @brief ワールドのロケーション取得
	XMFLOAT3 GetWorldLocation()const;

	//! @brief ワールドのスケール取得
	XMFLOAT3 GetWorldScale()const;

	//!
	//! @brief 行列更新時実行イベントを追加
	//! @param[in] event 追加するイベント
	//!
	void AddEventWhenMatrixUpdate(const std::function<void()>& event)
	{
		mEventWhenMatrixUpdate.emplace_back(event);
	};

	const XMFLOAT4X4& GetWorldMatrix()const
	{
		return mWorldMatrix;
	}

	const XMFLOAT4X4& GetLocalMatrix()const
	{
		return mLocalMatrix;
	}

	const bool& GetIsChild()const
	{
		return mIsChild;
	}

	void SetIsBillboard(bool flg)
	{
		mIsBillboard = flg;
	}

	void SetAttachOption(EAttachOption option)
	{
		mAttachOption = option;
	}

};