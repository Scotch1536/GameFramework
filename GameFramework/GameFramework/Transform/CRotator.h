#pragma once
#include <memory>
#include <DirectXMath.h>

#include "../Library/LCMath.h"

using namespace DirectX;

class CTransform;

//���[�e�[�^�[�N���X
class CRotator
{
private:
	CTransform& mPartner;

	XMFLOAT4 mQuaternion;				//�N�H�[�^�j�I���i���ݒn�j
	XMFLOAT4 mLastFrameQuaternion;		//1�t���[���O�̃N�H�[�^�j�I��

	bool mIsSameQuaternionToBeforeFrame = true;			//��r���ʁi���̃t���[���̊p�x�ƑO�̃t���[���p�x�́j

public:
	CRotator(CTransform& partner);

	//�X�V
	bool Update();

	//�}�g���b�N�X�擾
	XMFLOAT4X4 GenerateMatrix();

	//�w��̈ʒu�Ɋp�x��ύX����
	void ChangeQuaternionToLocation(XMFLOAT3 location);

	//�w��̈ʒu�Ɍ����N�H�[�^�j�I�����Q�b�g����
	void CalcQuaternionToLocation(XMFLOAT3 location , XMFLOAT4& resultQua);

	const XMFLOAT4& GetQuaternion()const
	{
		return mQuaternion;
	}

	const bool& GetIsSameQuaternionToBeforeFrame()const
	{
		return mIsSameQuaternionToBeforeFrame;
	}

	void SetQuaternion(const XMFLOAT4& qua)
	{
		mQuaternion = qua;
	}

	void SetAngle(const XMFLOAT3& angle);

	void AddAngle(const XMFLOAT3& angle);

};