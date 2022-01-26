#pragma once
#include <memory>
#include "CComponent.h"

//!
//! @file
//! @brief �X�v�����O�A�[���R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

class CTransform;
class CCameraComponent;

//! @brief �ڑ����[�h�񋓌^
enum class ELinkMode
{
	ALL_LINK ,				//!< ���ׂẴg�����X�t�H�[����ڑ�
	LOCATION_ONLY_LINK ,	//!< ���P�[�V�������̂ݐڑ�
};

//!< @brief �X�v�����O�A�[���R���|�[�l���g�N���X
class CSpringArmComponent :public CComponent
{
private:
	ELinkMode mSyncMode = ELinkMode::ALL_LINK;		//!< �ڑ����[�h

	const CTransform& mTargetTransform;				//!< �^�[�Q�b�g�̃g�����X�t�H�[��
	CCameraComponent& mPartnerCamera;				//!< �p�[�g�i�[�J����

	std::unique_ptr<XMFLOAT4X4> mIdealMatrix;		//!< ���z�̍s��

	float mLerpTime = 0.0f;							//!< ���`��Ԃ̃A���t�@�l��0�`1�܂łɂ�����b��
	float mAlpha = 0.0f;							//!< �A���t�@�l
	float mIncrementAlpha = 0.0f;					//!< �A���t�@�l�̑�����

	//! @brief �X�V
	void Update()override;

	//! @brief �A���t�@�l�̑���
	void IncreaseAlpha();

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�̏��L��
	//! @param[in] targetTrans �^�[�Q�b�g�̃g�����X�t�H�[��
	//! @param[in] partnerCamera �p�[�g�i�[�ƂȂ�J����
	//! @param[in] linkMode �ڑ����[�h�J����
	//! @param[in] priority �D��x
	//!
	CSpringArmComponent(CActor& owner , const CTransform& targetTrans , CCameraComponent& partnerCamera , ELinkMode linkMode = ELinkMode::ALL_LINK , int priority = 10);

	const ELinkMode& GetLinkMode()
	{
		return mSyncMode;
	}

	void SetLinkMode(ELinkMode mode)
	{
		mSyncMode = mode;
	}

	void SetLerpTime(float time)
	{
		mLerpTime = time;

		//�A���t�@�l�̑����ʂ̌v�Z
		mIncrementAlpha = 1.0f / (60.0f * mLerpTime);
	}

};