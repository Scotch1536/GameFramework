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

	XMFLOAT4X4 mLocalMatrix;						//���[�J���s��
	const CTransform& mParentTransform;				//�e�g�����X�t�H�[��
	CCameraComponent& mUseCamera;					//�g���J����

	XMFLOAT3 mInitEye;			//�������Ɏg���J�����ʒu
	XMFLOAT3 mInitLockAt;		//�������Ɏg�������_
	XMFLOAT3 mInitUp;			//�������Ɏg��������x�N�g��

	std::unique_ptr<XMFLOAT4X4> mResultWorldMatrix;			//���ʂ̃��[���h�s��
	std::unique_ptr<XMFLOAT3> mResultEye;					//���ʂ̃J�����ʒu
	std::unique_ptr<XMFLOAT3> mResultLockAt;				//���ʂ̒����_
	std::unique_ptr<XMFLOAT3> mResultUp;					//���ʂ̏�����x�N�g��

	float mLerpTime = 0.0f;
	float mAlpha = 1.0f;
	float mIncrementAlpha = 1.0f;

	//���[�J���s��̍X�V
	void UpdateLocalMatrix();

	//���`��Ԃ̃A���t�@�����l���v�Z���ăZ�b�g
	void IncreaseAlpha();

	//�ڕW�̃��Z�b�g
	void ResetGoal();

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

		mUseCamera.SetView(mInitEye , mInitLockAt , mInitUp);

		ResetGoal();
	}

	void SetLerpTime(float time)
	{
		mLerpTime = time;
		mIncrementAlpha = 1.0f / (60.0f * mLerpTime);
	}
};