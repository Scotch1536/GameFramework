#pragma once
#include <memory>
#include "CComponent.h"

class CTransform;
class CCameraComponent;

class CSpringArmComponent :public CComponent
{
public:
	enum class EMovement
	{
		TARGET_SYNC ,
		FOLLOW_BEHIND ,
	};

private:
	EMovement mMovement = EMovement::TARGET_SYNC;		//カメラの動き方

	const CTransform& mTargetTransform;			//対象のトランスフォーム
	CCameraComponent& mUseCamera;				//使うカメラ

	std::unique_ptr<XMFLOAT3> mGoalCameraLocation;			//目標のカメラ位置
	XMFLOAT3 mDistance = { 0.f,0.f,0.f };					//距離

	float mTimeToGoal = 0;					//目標にかかる時間
	float mIncrementAlpha = 0;				//線形補間のアルファ増加値

public:
	CSpringArmComponent(CActor& owner , const CTransform& targetTrans , CCameraComponent& useCamera , float time , EMovement move = EMovement::TARGET_SYNC , int priority = 10);

	void Update()override;

	void SetMovement(EMovement move)
	{
		mMovement = move;
	}

	void SetTimeToGoal(float time)
	{
		mTimeToGoal = time;
		mIncrementAlpha = 1.0f / (60 * mTimeToGoal);
	}
};