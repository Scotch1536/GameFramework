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

	std::unique_ptr<XMFLOAT4X4> mGoalWorldMatrix;
	std::unique_ptr<XMFLOAT3> mGoalEye;
	std::unique_ptr<XMFLOAT3> mGoalLockAt;
	std::unique_ptr<XMFLOAT3> mGoalUp;

	float mLerpTime = 0.0f;
	float mAlpha = 1.0f;
	float mIncrementAlpha = 1.0f;

	//ローカル行列の更新
	void UpdateLocalMatrix();

	void IncreaseAlpha();

	void ResetPalam()
	{
		mGoalWorldMatrix.reset();
		mGoalEye.reset();
		mGoalLockAt.reset();
		mGoalUp.reset();
	}
public:
	CSpringArmComponent(CActor& owner , const CTransform& parentTrans , CCameraComponent& useCamera , ESyncMode syncMode = ESyncMode::ALL_SYNC , int priority = 10);

	void Update()override;

	const ESyncMode& GetSyncMode()
	{
		return mSyncMode;
	}

	void SetSyncMode(ESyncMode move)
	{
		mSyncMode = move;

		ResetPalam();
	}

	void SetLerpTime(float time)
	{
		mLerpTime = time;
		mIncrementAlpha = 1.0f / (60 * mLerpTime);
	}
};