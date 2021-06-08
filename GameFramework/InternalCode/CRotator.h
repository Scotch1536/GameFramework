#pragma once
#include <memory>
#include "dx11mathutil.h"

class CTransform;

class CRotator
{
private:
	float mAlpha;					//Slerp�Ŏg�p����A���t�@�l
	float mIncreaceAlpha;			//�A���t�@�̑����l

	XMFLOAT3 mAngle;				//�p�x�i�x���@�j
	XMFLOAT4 mQuaternion;			//�N�H�[�^�j�I���i���ݒn�j

	//XMFLOAT4X4 mMatrix;			//�}�g���b�N�X

	std::unique_ptr<XMFLOAT4> mFromQuaternion;			//�N�H�[�^�j�I���i�ړ��O�j
	std::unique_ptr<XMFLOAT4> mToQuaternion;			//�N�H�[�^�j�I���i�ړ���j
	
	//�I�C���[�p����N�H�[�^�j�I���ɕϊ�
	void TransformFromEulerAnglesToQuaternion(const XMFLOAT3& angle, XMFLOAT4& qua);

	//�N�H�[�^�j�I������I�C���[�p�ɕϊ�
	void TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua , XMFLOAT3& angle);
public :
	CRotator();

	////������
	//void Init();

	//�X�V
	void Update();

	//�p�x�Z�b�g
	void SetAngle(XMFLOAT3 angle /*,float time*/);

	void RequestSLerp(XMFLOAT3 angle , float time);

	//�}�g���b�N�X�擾
	XMFLOAT4X4 GenerateMatrix(CTransform& partner);
};