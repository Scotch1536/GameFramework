#pragma once
#include "dx11mathutil.h"
#include <memory>

class CRotator
{
private:
	float mAlpha;
	float mInc;

	XMFLOAT3 mAngle;	//�p�x�i�x���@�j
	XMFLOAT4X4 mMtx;	//�}�g���b�N�X
	XMFLOAT4 mQua;		//�N�H�[�^�j�I���i���ݒn�j
	std::unique_ptr<XMFLOAT4> mStartQua;	//�N�H�[�^�j�I���i�ړ��O�j
	std::unique_ptr<XMFLOAT4> mGoalQua;		//�N�H�[�^�j�I���i�ړ���j
	
public :
	CRotator() {};

	//������
	void Init();

	//�X�V
	void Update();

	//�p�x�Z�b�g
	void SetAngle(XMFLOAT3 angle ,float time);

	//�}�g���b�N�X�擾
	XMFLOAT4X4 GetMtx();

	//�I�C���[�p����N�H�[�^�j�I���ɕϊ�
	void EulerAnglesToQuaternion(XMFLOAT3 angle, XMFLOAT4 qua);
};