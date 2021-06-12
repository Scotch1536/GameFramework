#pragma once
#include <memory>
#include <DirectXMath.h>

using namespace DirectX;

class CTransform;
class CChildTransform;

//���[�e�[�^�[�N���X
class CRotator
{
private:
	XMFLOAT4 mQuaternion;							//�N�H�[�^�j�I���i���ݒn�j
	XMFLOAT3 mLastFrameAngle = { 0.f,0.f,0.f };		//��r���邽�߂̊p�x

	bool mIsSameAngle = true;		//��r���ʁi���̃t���[���̊p�x�ƑO�̃t���[���p�x�́j

public:
	XMFLOAT3 Angle = { 0.f,0.f,0.f };			//�p�x�i�x���@�j

	CRotator();

	//�X�V
	bool Update();

	//�}�g���b�N�X�擾
	XMFLOAT4X4 GenerateMatrix(CTransform& partner);

	const XMFLOAT4& GetQuaternion()const
	{
		return mQuaternion;
	}

	const bool& GetIsSameAngle()const
	{
		return mIsSameAngle;
	}

	void SetQuaternion(CChildTransform& partner , XMFLOAT4& qua)
	{
		mQuaternion = qua;
	}
};