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

	//ローカル行列の更新
	void UpdateLocalMatrix();

public:
	CSpringArmComponent(CActor& owner , const CTransform& parentTrans , CCameraComponent& useCamera , ESyncMode syncMode = ESyncMode::ALL_SYNC , int priority = 10);

	void Update()override;

	void SetMovement(ESyncMode move)
	{
		mSyncMode = move;
	}
};