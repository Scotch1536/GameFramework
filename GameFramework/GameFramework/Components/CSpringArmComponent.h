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
	ESyncMode mSyncMode = ESyncMode::ALL_SYNC;		//�J�����̓�����

	const CTransform& mParentTransform;				//�e�g�����X�t�H�[��
	CCameraComponent& mUseCamera;					//�g���J����

	std::unique_ptr<XMFLOAT4X4> mIdealMatrix;		//���ʂ̃��[���h�s��

	float mLerpTime = 0.0f;
	float mAlpha = 0.0f;
	float mIncrementAlpha = 0.0f;

	//���`��Ԃ̃A���t�@�����l���v�Z���ăZ�b�g
	void IncreaseAlpha();

	void Update()override;

public:
	CSpringArmComponent(CActor& owner , const CTransform& parentTrans , CCameraComponent& useCamera , ESyncMode syncMode = ESyncMode::ALL_SYNC , int priority = 10);

	const ESyncMode& GetSyncMode()
	{
		return mSyncMode;
	}

	void SetSyncMode(ESyncMode mode)
	{
		mSyncMode = mode;
	}

	void SetLerpTime(float time)
	{
		mLerpTime = time;
		mIncrementAlpha = 1.0f / (60.0f * mLerpTime);
	}

};