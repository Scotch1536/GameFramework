#pragma once
#include <vector>
#include <memory>
#include <array>
#include <functional>
#include <DirectXMath.h>

#include "CRotator.h"

class CChildTransform;
class IActor;

//トランスフォームクラス
class CTransform
{
private:
	XMFLOAT4X4 mWorldMatrixSelf;			//自身のワールド行列
	XMFLOAT4X4 mWorldMatrixResult;			//最終的な結果のワールド行列

	CTransform* mParentTransform = nullptr;				//親トランスフォーム
	std::vector<CTransform*> mChildTransform;			//子トランスフォーム

	XMFLOAT3 mLastFrameLocation = { 0.f,0.f,0.f };		//前フレームのロケーション
	XMFLOAT3 mLastFrameScale = { 0.f,0.f,0.f };			//前フレームのスケール

	IActor& mOwnerInterface;

	std::vector<std::function<void()>> mMatrixUpdateTimeFunction;		//マトリックス更新時実行関数

	bool mShouldUpdateMatrix = true;		//マトリックスを更新すべきか
	bool mIsChild = false;					//自分が子トランスフォームか
	bool mIsBillboard = false;				//ビルボードかどうか
	bool mDoDrawDebugLine = false;			//デバッグラインを描画するか

public:
	XMFLOAT3 Location = { 0.f,0.f,0.f };		//ロケーション
	XMFLOAT3 Scale = { 1.f,1.f,1.f };			//スケール

	CRotator Rotation;			//ローテーション

	//アクターを作るとき限定のコンストラクタ
	CTransform(IActor& partner);

	//作るときから従属するトランスフォームが決まっている時のコンストラクタ
	CTransform(IActor& partner , CTransform& parentTrans);

	~CTransform();

	//更新
	void Update();

	//行列をDirectxにセットしてもらうリクエスト
	void RequestSetMatrix();

	//引数のトランスフォームをアタッチ（親子付け）する
	void AttachTransform(CTransform& attachTarget);

	//引数のトランスフォームをデタッチ（親子付け解除）する
	void DetachTransform(CTransform& detachTarget);

	void RequestDebugLine();

	const XMFLOAT4X4& GetWorldMatrixResult()const
	{
		return mWorldMatrixResult;
	}

	const bool& GetIsChild()const
	{
		return mIsChild;
	}

	XMFLOAT3 GetRightVector()const;

	XMFLOAT3 GetUpwardVector()const;

	XMFLOAT3 GetForwardVector()const;

	XMFLOAT3 GetWorldLocation()const;

	XMFLOAT3 GetWorldScale()const;

	XMFLOAT3 GetWorldRotatorAngle()const;

	void SetIsBillboard(bool flg)
	{
		mIsBillboard = flg;
	}

	void AddMatrixUpdateTimeFunction(const std::function<void()>& func)
	{
		mMatrixUpdateTimeFunction.emplace_back(func);
	};

};