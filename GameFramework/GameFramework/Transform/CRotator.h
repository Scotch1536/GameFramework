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
	const CTransform& mPartner;

	XMFLOAT4 mQuaternion;		//�N�H�[�^�j�I���i���ݒn�j

	XMFLOAT3 mAngle = { 0.f,0.f,0.f };				//�p�x�i�x���@�j
	XMFLOAT3 mLastFrameAngle = { 0.f,0.f,0.f };		//1�t���[���O�̊p�x�i�x���@�j

	bool mIsSameAngle = true;				//��r���ʁi���̃t���[���̊p�x�ƑO�̃t���[���p�x�́j

	void UpdateAngle(float& angle);

public:
	CRotator(const CTransform& partner);

	//�X�V
	bool Update();

	//�}�g���b�N�X�擾
	XMFLOAT4X4 GenerateMatrix();

	//�w��̈ʒu�Ɋp�x��ύX����
	void ChangeAngleToLocation(XMFLOAT3 location);

	const XMFLOAT4& GetQuaternion()const
	{
		return mQuaternion;
	}

	const XMFLOAT3& GetAngle()const
	{
		return mAngle;
	}

	const bool& GetIsSameAngle()const
	{
		return mIsSameAngle;
	}

	void SetQuaternion(const XMFLOAT4& qua)
	{
		mQuaternion = qua;
	}

	void SetAngle(const XMFLOAT3& angle);

	void AddAngle(const XMFLOAT3& angle);

};