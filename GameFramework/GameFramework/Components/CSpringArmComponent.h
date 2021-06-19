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

	//���[�J���s��̍X�V
	void UpdateLocalMatrix();

public:
	CSpringArmComponent(CActor& owner , const CTransform& parentTrans , CCameraComponent& useCamera , ESyncMode syncMode = ESyncMode::ALL_SYNC , int priority = 10);

	void Update()override;

	void SetMovement(ESyncMode move)
	{
		mSyncMode = move;
	}
};