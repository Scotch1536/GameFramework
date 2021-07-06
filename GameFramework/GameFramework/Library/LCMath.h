#pragma once
#include <DirectXMath.h>

using namespace DirectX;

static class LCMath
{
public:
	//�I�C���[�p����N�H�[�^�j�I���ɕϊ�
	static void TransformFromEulerAnglesToQuaternion(const XMFLOAT3& angle , XMFLOAT4& ansQua);

	//�N�H�[�^�j�I������I�C���[�p�ɕϊ�
	//static void TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua , XMFLOAT3& angle);

	//���P�[�V�����A�X�P�[���A��]�s�񂩂�w��̍s����X�V
	static void UpdateMatrix(const XMFLOAT3& location , const XMFLOAT3& scale , const XMFLOAT4X4& rotMTX , XMFLOAT4X4& result);

	//�w���Float3���m����v���Ă��邩�̔�r
	static bool CompareFloat3(const XMFLOAT3& target1 , const XMFLOAT3& target2);

	//�w��̍s�񓯎m����v���Ă��邩�̔�r
	static bool CompareMatrix(const XMFLOAT4X4& target1 , const XMFLOAT4X4& target2);

	//�X�^�[�g����S�[���ւ̃x�N�g�����Q�b�g
	static void CalcFloat3FromStartToGoal(const XMFLOAT3& start , const XMFLOAT3& goal , XMFLOAT3& ansVec);

	static void CalcFloat3Length(const XMFLOAT3& target , float& ansLength);

	static void CalcFloat3Normalize(const XMFLOAT3& target , XMFLOAT3& ansvec);

	//���`���
	static float Lerp(float start , float end , float alpha);
	static XMFLOAT3 Lerp(const XMFLOAT3& start , const XMFLOAT3& end , float alpha);
};