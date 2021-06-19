#pragma once
#include <DirectXMath.h>

using namespace DirectX;

static class LCMath
{
public:
	//�I�C���[�p����N�H�[�^�j�I���ɕϊ�
	static void TransformFromEulerAnglesToQuaternion(const XMFLOAT3& angle , XMFLOAT4& qua);

	//�N�H�[�^�j�I������I�C���[�p�ɕϊ�
	static void TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua , XMFLOAT3& angle);

	//���P�[�V�����A�X�P�[���A��]�s�񂩂�w��̍s����X�V
	static void UpdateMatrix(const XMFLOAT3& location , const XMFLOAT3& scale , XMFLOAT4X4 rotMTX , XMFLOAT4X4& result);

	//�w���Float3���m����v���Ă��邩�̔�r
	static bool CompareFloat3(const XMFLOAT3& target1 , const XMFLOAT3& target2);

	//���`���
	static float Lerp(float start , float end , float alpha);
};