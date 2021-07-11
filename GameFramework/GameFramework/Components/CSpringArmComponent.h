#pragma once
#include <memory>
#include "CComponent.h"

class CTransform;
class CCameraComponent;

enum class ESyncMode
{
	ALL_SYNC ,
	LOCATION_ONLY_SYNC ,
};

class CSpringArmComponent :public CComponent
{
private:
	ESyncMode mSyncMode = ESyncMode::ALL_SYNC;		//カメラの動き方

	XMFLOAT4X4 mLocalMatrix;						//ローカル行列
	const CTransform& mParentTransform;				//親トランスフォーム
	CCameraComponent& mUseCamera;					//使うカメラ

	XMFLOAT3 mInitEye;			//初期化に使うカメラ位置
	XMFLOAT3 mInitLockAt;		//初期化に使う注視点
	XMFLOAT3 mInitUp;			//初期化に使う上向きベクトル

	std::unique_ptr<XMFLOAT4X4> mGoalWorldMatrix;		//目標のワールド行列
	std::unique_ptr<XMFLOAT3> mGoalEye;					//目標のカメラ位置
	std::unique_ptr<XMFLOAT3> mGoalLockAt;				//目標の注視点
	std::unique_ptr<XMFLOAT3> mGoalUp;					//目標の上向きベクトル

	float mLerpTime = 0.0f;
	float mAlpha = 1.0f;
	float mIncrementAlpha = 1.0f;

	//ローカル行列の更新
	void UpdateLocalMatrix();

	//線形補間のアルファ増加値を計算してセット
	void IncreaseAlpha();

	//目標のリセット
	void ResetGoal();

public:
	CSpringArmComponent(CActor& owner , const CTransform& parentTrans , CCameraComponent& useCamera , ESyncMode syncMode = ESyncMode::ALL_SYNC , int priority = 10);

	void Update()override;

	const ESyncMode& GetSyncMode()
	{
		return mSyncMode;
	}

	void SetSyncMode(ESyncMode mode)
	{
		mSyncMode = mode;

		mUseCamera.SetView(mInitEye , mInitLockAt , mInitUp);

		ResetGoal();
	}

	void SetLerpTime(float time)
	{
		mLerpTime = time;
		mIncrementAlpha = 1.0f / (60.0f * mLerpTime);
	}
};