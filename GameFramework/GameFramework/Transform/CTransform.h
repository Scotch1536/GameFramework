#pragma once
#include <vector>
#include <memory>
#include <DirectXMath.h>

#include "CRotator.h"

class CChildTransform;
class CActor;

class ITransform
{
public:
	virtual ~ITransform() {};
	virtual void AttachChildTransform(CChildTransform& targetChild) = 0;
};

//トランスフォームクラス
class CTransform :public ITransform
{
private:
	std::vector<CTransform*> mChildTransform;			//従属するの子トランスフォーム

	XMFLOAT3 mCompareLocation = { 0.f,0.f,0.f };		//比較するためのロケーション
	XMFLOAT3 mCompareScale = { 0.f,0.f,0.f };			//比較するためのスケール

	//子トランスフォームの追加
	void AttachChildTransform(CChildTransform& targetChild)override;
protected:
	XMFLOAT4X4 mWorldMatrix;		//ワールド行列

	bool mShouldUpdateMatrix = true;		//行列を更新すべきか

	CTransform();

public:
	XMFLOAT3 Location = { 0.f,0.f,0.f };			//ロケーション
	XMFLOAT3 Scale = { 1.f,1.f,1.f };				//スケール

	CRotator Rotation;								//ローテーション

	CTransform(CActor& partner);
	virtual ~CTransform() = default;

	//更新
	virtual void Update();

	//行列をDirectxにセットしてもらうリクエスト
	virtual void RequestSetMatrix();

	//引数の子コンポーネントとの親子関係をを切り離す
	void DetachChildTransform(CChildTransform& targetChild);

	const XMFLOAT4X4& GetWorldMatrix(const CChildTransform& child)const
	{
		return mWorldMatrix;
	}
};