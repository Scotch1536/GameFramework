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
	EMovement mMovement = EMovement::TARGET_SYNC;		//�J�����̓�����

	const CTransform& mTargetTransform;			//�Ώۂ̃g�����X�t�H�[��
	CCameraComponent& mUseCamera;				//�g���J����

	std::unique_ptr<XMFLOAT3> mGoalCameraLocation;			//�ڕW�̃J�����ʒu
	XMFLOAT3 mDistance = { 0.f,0.f,0.f };					//����

	float mTimeToGoal = 0;					//�ڕW�ɂ����鎞��
	float mIncrementAlpha = 0;				//���`��Ԃ̃A���t�@�����l

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