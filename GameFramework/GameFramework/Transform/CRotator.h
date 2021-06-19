#pragma once
#include <memory>
#include <DirectXMath.h>

using namespace DirectX;

class CTransform;

//���[�e�[�^�[�N���X
class CRotator
{
private:
	XMFLOAT4 mQuaternion;							//�N�H�[�^�j�I���i���ݒn�j
	XMFLOAT3 mLastFrameAngle = { 0.f,0.f,0.f };		//�O�t���[���̊p�x

	bool mIsSameAngle = true;				//��r���ʁi���̃t���[���̊p�x�ƑO�̃t���[���p�x�́j
	bool mIsFirstTimeToUpdate = true;		//�X�V�����ڂ��ǂ���
public:
	XMFLOAT3 Angle = { 0.f,0.f,0.f };			//�p�x�i�x���@�j

	CRotator();

	//�X�V
	bool Update();

	//�}�g���b�N�X�擾
	XMFLOAT4X4 GenerateMatrix();

	const bool& GetIsSameAngle()const
	{
		return mIsSameAngle;
	}
};