#pragma once
#include <vector>
#include <memory>
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

	XMFLOAT3 mCompareLocation = { 0.f,0.f,0.f };		//比較するためのロケーション
	XMFLOAT3 mCompareScale = { 0.f,0.f,0.f };			//比較するためのスケール

	bool mShouldUpdateMatrix = true;		//行列を更新すべきか
	bool mIsChild = false;					//自分が子トランスフォームか

public:
	XMFLOAT3 Location = { 0.f,0.f,0.f };			//ロケーション
	XMFLOAT3 Scale = { 1.f,1.f,1.f };				//スケール

	CRotator Rotation;								//ローテーション

	CTransform();
	CTransform(IActor& partner);
	~CTransform();

	//更新
	virtual void Update();

	//行列をDirectxにセットしてもらうリクエスト
	virtual void RequestSetMatrix();

	//引数のトランスフォームをアタッチ（親子付け）する
	void AttachTransform(CTransform& attachTarget);

	//引数のトランスフォームをデタッチ（親子付け解除）する
	void DetachTransform(CTransform& detachTarget);

	const XMFLOAT4X4& GetWorldMatrixResult(const CTransform& partner)const
	{
		return mWorldMatrixResult;
	}

	const bool& GetIsChild()const
	{
		return mIsChild;
	}
};