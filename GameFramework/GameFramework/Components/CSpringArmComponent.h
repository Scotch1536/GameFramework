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

	XMFLOAT4X4 mLocalMatrix;						//���[�J���s��
	const CTransform& mParentTransform;				//�e�g�����X�t�H�[��
	CCameraComponent& mUseCamera;					//�g���J����

	//���[�J���s��̍X�V
	void UpdateLocalMatrix();

public:
	CSpringArmComponent(CActor& owner , const CTransform& parentTrans , CCameraComponent& useCamera , EMovement move = EMovement::TARGET_SYNC , int priority = 10);

	void Update()override;

	void SetMovement(EMovement move)
	{
		mMovement = move;
	}
};