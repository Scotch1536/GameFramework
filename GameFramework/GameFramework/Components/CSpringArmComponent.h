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

	XMFLOAT4X4 mLocalMatrix;						//ローカル行列
	const CTransform& mParentTransform;				//親トランスフォーム
	CCameraComponent& mUseCamera;					//使うカメラ

	//ローカル行列の更新
	void UpdateLocalMatrix();

public:
	CSpringArmComponent(CActor& owner , const CTransform& parentTrans , CCameraComponent& useCamera , EMovement move = EMovement::TARGET_SYNC , int priority = 10);

	void Update()override;

	void SetMovement(EMovement move)
	{
		mMovement = move;
	}
};