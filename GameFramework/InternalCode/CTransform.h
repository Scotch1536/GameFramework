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
	virtual void AddChildTransform(CChildTransform& child) = 0;
};

class CTransform :public ITransform
{
private:
	XMFLOAT4X4 mWorldMatrix;		//ワールド行列

	std::vector<CTransform*> mChildTransform;			//従属するの子トランスフォーム

	bool mShouldUpdateMatrix = true;		//行列を更新すべきか

	//子トランスフォームの追加
	void AddChildTransform(CChildTransform& child)override;
protected:
	XMFLOAT3 mLocation;			//ロケーション
	XMFLOAT3 mScale;			//スケール
	CRotator mRotation;			//ローテーション

	CTransform();
public:
	CTransform(CActor& partner);
	virtual ~CTransform() = default;

	//更新
	virtual void Update();

	//行列をDirectxにセットしてもらうリクエスト
	void RequestSetMatrix();

	//球面線形補間をリクエスト
	void RequestSLerp(XMFLOAT3 angle , float lerpTime)
	{
		mRotation.RequestSLerp(angle , lerpTime);
	}

	void SetLocation(XMFLOAT3 location)
	{
		mLocation = location;

		if(!mShouldUpdateMatrix)mShouldUpdateMatrix = true;
	}

	void SetScale(XMFLOAT3 scale)
	{
		mScale = scale;;

		if(!mShouldUpdateMatrix)mShouldUpdateMatrix = true;
	}

	void SetRotation(XMFLOAT3 rotation)
	{
		mRotation.SetAngle(rotation);

		if(!mShouldUpdateMatrix)mShouldUpdateMatrix = true;
	}

	const XMFLOAT3& GetLocation()const
	{
		return mLocation;
	}

	const XMFLOAT3& GetScale()const
	{
		return mScale;
	}

	const XMFLOAT3& GetRotation()const
	{
		return mRotation.GetAngle();
	}
};