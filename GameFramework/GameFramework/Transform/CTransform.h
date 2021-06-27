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

	XMFLOAT3 mLastFrameLocation = { 0.f,0.f,0.f };		//前フレームのロケーション
	XMFLOAT3 mLastFrameScale = { 0.f,0.f,0.f };			//前フレームのスケール

	bool mShouldUpdateMatrix = true;		//行列を更新すべきか
	bool mIsChild = false;					//自分が子トランスフォームか

public:
	XMFLOAT3 Location = { 0.f,0.f,0.f };			//ロケーション
	XMFLOAT3 Scale = { 1.f,1.f,1.f };				//スケール

	CRotator Rotation;								//ローテーション

	CTransform();

	/*
	コンポーネントにトランスフォームを作る時のコンストラクタ
	（アクターのトランスフォームに従属させる）
	*/
	CTransform(IActor& partner);

	~CTransform();

	//更新
	void Update();

	//行列をDirectxにセットしてもらうリクエスト
	void RequestSetMatrix();

	//引数のトランスフォームをアタッチ（親子付け）する
	void AttachTransform(CTransform& attachTarget);

	//引数のトランスフォームをデタッチ（親子付け解除）する
	void DetachTransform(CTransform& detachTarget);

	const XMFLOAT4X4& GetWorldMatrixResult()const
	{
		return mWorldMatrixResult;
	}

	const bool& GetIsChild()const
	{
		return mIsChild;
	}

	XMFLOAT3 GetRightVector()const
	{
		XMFLOAT3 result;

		result.x = mWorldMatrixResult._11 / Scale.x;
		result.y = mWorldMatrixResult._12 / Scale.y;
		result.z = mWorldMatrixResult._13 / Scale.z;

		return result;
	}

	XMFLOAT3 GetUpwardVector()const
	{
		XMFLOAT3 result;

		result.x = mWorldMatrixResult._21 / Scale.x;
		result.y = mWorldMatrixResult._22 / Scale.y;
		result.z = mWorldMatrixResult._23 / Scale.z;

		return result;
	}

	XMFLOAT3 GetForwardVector()const
	{
		XMFLOAT3 result;

		result.x = mWorldMatrixResult._31 / Scale.x;
		result.y = mWorldMatrixResult._32 / Scale.y;
		result.z = mWorldMatrixResult._33 / Scale.z;

		return result;
	}
};