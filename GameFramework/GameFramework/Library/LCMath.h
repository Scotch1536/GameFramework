#pragma once
#include <DirectXMath.h>

using namespace DirectX;

static class LCMath
{
public:
	//�I�C���[�p����N�H�[�^�j�I���ɕϊ�
	static const XMFLOAT4& TransformFromEulerAnglesToQuaternion(const XMFLOAT3& axisX , const XMFLOAT3& axisY , const XMFLOAT3& axisZ ,
		const XMFLOAT3& eulerAngle , XMFLOAT4& resultQua);

	//�N�H�[�^�j�I������I�C���[�p�ɕϊ�
	static const XMFLOAT3& TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua , XMFLOAT3& resultAngle);

	//���P�[�V�����A�X�P�[���A��]�s�񂩂�w��̍s����X�V
	static const XMFLOAT4X4& UpdateMatrix(const XMFLOAT3& location , const XMFLOAT3& scale , const XMFLOAT4X4& rotMTX , XMFLOAT4X4& resultMTX);

	//�w���Float3���m����v���Ă��邩�̔�r
	static bool CompareFloat3(const XMFLOAT3& target1 , const XMFLOAT3& target2);

	//�w��̍s�񓯎m����v���Ă��邩�̔�r
	static bool CompareMatrix(const XMFLOAT4X4& target1 , const XMFLOAT4X4& target2);

	//���i�����x�N�g���j�Ɗp�x(���W�A��)����N�H�[�^�j�I�����쐬	
	static const XMFLOAT4& CreateFromAxisAndAngleToQuaternion(const XMFLOAT3& axis , const float& angle , XMFLOAT4& resultQua);

	static const XMFLOAT4& CalcQuaternionToLocation(const XMFLOAT3& currentLocation , const XMFLOAT3& currentOrienVec , const XMFLOAT3& location , XMFLOAT4& resultQua);

	static const XMFLOAT4& CalcQuaternionMultiply(const XMFLOAT4& qua1 , const XMFLOAT4& qua2 , XMFLOAT4& result);

	//�X�^�[�g����S�[���ւ̃x�N�g�����Q�b�g
	static const XMFLOAT3& CalcFloat3FromStartToGoal(const XMFLOAT3& start , const XMFLOAT3& goal , XMFLOAT3& resultVec);

	static const float& CalcFloat3Length(const XMFLOAT3& target , float& resultLen);

	static const XMFLOAT3& CalcFloat3Normalize(const XMFLOAT3& target , XMFLOAT3& resultVec);

	static const float& CalcFloat3Dot(const XMFLOAT3& target1 , const XMFLOAT3& target2 , float& resultScaler);

	static const XMFLOAT3& CalcFloat3Cross(const XMFLOAT3& target1 , const XMFLOAT3& target2 , XMFLOAT3& resultVec);

	//���`���
	static const float& Lerp(const float& start , const float& end , const float& alpha , float& result);
	static const XMFLOAT3& Lerp(const XMFLOAT3& start , const XMFLOAT3& end , const float& alpha , XMFLOAT3& result);
};