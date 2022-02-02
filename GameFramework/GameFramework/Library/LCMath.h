//!
//!	@file
//!	@brief ���w���C�u�����̃w�b�_�[�t�@�C��
//!

#pragma once
#include <vector>
#include <DirectXMath.h>

using namespace DirectX;

//! @brief ���w���C�u�����N���X
static class LCMath
{
public:
	//!
	//! @brief �I�C���[�p����N�H�[�^�j�I���ɕϊ�
	//! @param[in] axisX X�̉�]��
	//! @param[in] axisY Y�̉�]��
	//! @param[in] axisZ Z�̉�]��
	//! @param[in] eulerAngle �I�C���[�p
	//! @param[out] result ���ʂ̃N�H�[�^�j�I��
	//! @return const XMFLOAT4& ���ʂ̃N�H�[�^�j�I��
	//!
	static const XMFLOAT4& TransformFromEulerAnglesToQuaternion(const XMFLOAT3& axisX , const XMFLOAT3& axisY , const XMFLOAT3& axisZ ,
		const XMFLOAT3& eulerAngle , XMFLOAT4& result);

	//!
	//! @brief �I�C���[�p����N�H�[�^�j�I���ɕϊ�
	//! @param[in] axisX X�̉�]��
	//! @param[in] axisY Y�̉�]��
	//! @param[in] axisZ Z�̉�]��
	//! @param[in] eulerAngle �I�C���[�p
	//! @return XMFLOAT4& ���ʂ̃N�H�[�^�j�I��
	//!
	static XMFLOAT4 TransformFromEulerAnglesToQuaternion(const XMFLOAT3& axisX , const XMFLOAT3& axisY , const XMFLOAT3& axisZ ,
		const XMFLOAT3& eulerAngle);

	//!
	//! @brief �N�H�[�^�j�I������I�C���[�p�ɕϊ�
	//! @param[in] target �ϊ�����N�H�[�^�j�I��
	//! @param[out] result ���ʂ̃I�C���[�p
	//! @return const XMFLOAT3& ���ʂ̃I�C���[�p
	//!
	static const XMFLOAT3& TransformFromQuaternionToEulerAngles(const XMFLOAT4& target , XMFLOAT3& result);

	//!
	//! @brief �N�H�[�^�j�I������I�C���[�p�ɕϊ�
	//! @param[in] target �ϊ�����N�H�[�^�j�I��
	//! @return XMFLOAT3 ���ʂ̃I�C���[�p
	//!
	static XMFLOAT3 TransformFromQuaternionToEulerAngles(const XMFLOAT4& target);

	//!
	//! @brief �s�񂩂�I�C���[�p�ɕϊ�
	//! @param[in] target �ϊ�����s��
	//! @param[out] result ���ʂ̃I�C���[�p
	//! @return const XMFLOAT3& ���ʂ̃I�C���[�p
	//!
	static const XMFLOAT3& TransformFromMatrixToEulerAngles(const XMFLOAT4X4& target , XMFLOAT3& result);

	//!
	//! @brief �s�񂩂�I�C���[�p�ɕϊ�
	//! @param[in] target �ϊ�����s��
	//! @return XMFLOAT3 ���ʂ̃I�C���[�p
	//!
	static XMFLOAT3 TransformFromMatrixToEulerAngles(const XMFLOAT4X4& target);

	//!
	//! @brief �N�H�[�^�j�I�����s��ɕϊ�
	//! @param[in] target �ϊ�����N�H�[�^�j�I��
	//! @param[out] result ���ʂ̍s��
	//! @return const XMFLOAT4X4& ���ʂ̍s��
	//!
	static const XMFLOAT4X4& TransformFromQuaternionToMatrix(const XMFLOAT4& target , XMFLOAT4X4& result);

	//!
	//! @brief �N�H�[�^�j�I�����s��ɕϊ�
	//! @param[in] target �ϊ�����N�H�[�^�j�I��
	//! @return XMFLOAT4X4 ���ʂ̍s��
	//!
	static XMFLOAT4X4 TransformFromQuaternionToMatrix(const XMFLOAT4& target);

	//!
	//! @brief �P�ʍs��
	//! @param[in,out] target �P�ʍs�񉻂������s��,���ʂ̍s��
	//!
	static void IdentityMatrix(XMFLOAT4X4& target);

	//!
	//! @brief �P�ʃN�H�[�^�j�I����
	//! @param[in,out] target �P�ʃN�H�[�^�j�I�����������N�H�[�^�j�I��,���ʂ̃N�H�[�^�j�I��
	//!
	static void IdentityQuaternion(XMFLOAT4& target);

	//!
	//! @brief ���P�[�V�����A�X�P�[���A��]�s�񂩂�w��̍s����쐬
	//! @param[in] location ���P�[�V����
	//! @param[in] scale �X�P�[��
	//! @param[in] rotMTX ��]�s��
	//! @param[out] result ���ʂ̍s��
	//! @return const XMFLOAT4X4& ���ʂ̍s��
	//!
	static const XMFLOAT4X4& CreateMatrix(const XMFLOAT3& location , const XMFLOAT3& scale , const XMFLOAT4X4& rotMTX , XMFLOAT4X4& result);

	//!
	//! @brief ���P�[�V�����A�X�P�[���A��]�s�񂩂�w��̍s����쐬
	//! @param[in] location ���P�[�V����
	//! @param[in] scale �X�P�[��
	//! @param[in] rotMTX ��]�s��
	//! @return XMFLOAT4X4 ���ʂ̍s��
	//!
	static XMFLOAT4X4 CreateMatrix(const XMFLOAT3& location , const XMFLOAT3& scale , const XMFLOAT4X4& rotMTX);

	//!
	//! @brief �t�s����擾
	//! @param[in] target �t�s��ɂ������s��
	//! @param[out] result ���ʂ̍s��
	//! @return const XMFLOAT4X4& ���ʂ̍s��
	//!
	static const XMFLOAT4X4& InverseMatrix(const XMFLOAT4X4& target , XMFLOAT4X4& result);

	//!
	//! @brief �t�s����擾
	//! @param[in] target �t�s��ɂ������s��
	//! @return XMFLOAT4X4 ���ʂ̍s��
	//!
	static XMFLOAT4X4 InverseMatrix(const XMFLOAT4X4& target);

	//!
	//! @brief �]�u�s����擾
	//! @param[in] target �]�u�s��ɂ������s��
	//! @param[out] result ���ʂ̍s��
	//! @return const XMFLOAT4X4& ���ʂ̍s��
	//!
	static const XMFLOAT4X4& TransposeMatrix(const XMFLOAT4X4& target , XMFLOAT4X4& result);

	//!
	//! @brief �]�u�s����擾
	//! @param[in] target �]�u�s��ɂ������s��
	//! @return XMFLOAT4X4 ���ʂ̍s��
	//!
	static XMFLOAT4X4 TransposeMatrix(const XMFLOAT4X4& target);

	//!
	//! @brief �w���Float3���m����v���Ă��邩�̔�r
	//! @param[in] target1 ��r�Ώ�1
	//! @param[in] target2 ��r�Ώ�2
	//! @return bool ��v���Ă��邩
	//!
	static bool CompareFloat3(const XMFLOAT3& target1 , const XMFLOAT3& target2);

	//!
	//! @brief �w���Float4���m����v���Ă��邩�̔�r
	//! @param[in] target1 ��r�Ώ�1
	//! @param[in] target2 ��r�Ώ�2
	//! @return bool ��v���Ă��邩
	//!
	static bool CompareFloat4(const XMFLOAT4& target1 , const XMFLOAT4& target2);

	//!
	//! @brief �w��̍s�񓯎m����v���Ă��邩�̔�r
	//! @param[in] target1 ��r�Ώ�1
	//! @param[in] target2 ��r�Ώ�2
	//! @return bool ��v���Ă��邩
	//!
	static bool CompareMatrix(const XMFLOAT4X4& target1 , const XMFLOAT4X4& target2);

	//!
	//! @brief ���i�����x�N�g���j�Ɗp�x�i���W�A���j����N�H�[�^�j�I�����쐬
	//! @param[in] axis ��
	//! @param[in] angleOfRadian �p�x
	//! @param[out] result ���ʂ̃N�H�[�^�j�I��
	//! @return const XMFLOAT4& ���ʂ̃N�H�[�^�j�I��
	//!
	static const XMFLOAT4& CreateFromAxisAndAngleToQuaternion(const XMFLOAT3& axis , const float& angleOfRadian , XMFLOAT4& result);

	//!
	//! @brief ���i�����x�N�g���j�Ɗp�x�i���W�A���j����N�H�[�^�j�I�����쐬
	//! @param[in] axis ��
	//! @param[in] angleOfRadian �p�x
	//! @return XMFLOAT4 ���ʂ̃N�H�[�^�j�I��
	//!
	static XMFLOAT4 CreateFromAxisAndAngleToQuaternion(const XMFLOAT3& axis , const float& angleOfRadian);

	//!
	//! @brief �N�H�[�^�j�I�����m�̏�Z
	//! @param[in] target1 ��Z����1�ڂ̃N�H�[�^�j�I��
	//! @param[in] target2 ��Z����2�ڂ̃N�H�[�^�j�I��
	//! @param[out] result ���ʂ̃N�H�[�^�j�I��
	//! @return const XMFLOAT4& ���ʂ̃N�H�[�^�j�I��
	//!
	static const XMFLOAT4& CalcQuaternionMultiply(const XMFLOAT4& target1 , const XMFLOAT4& target2 , XMFLOAT4& result);

	//!
	//! @brief �N�H�[�^�j�I�����m�̏�Z
	//! @param[in] target1 ��Z����1�ڂ̃N�H�[�^�j�I��
	//! @param[in] target2 ��Z����2�ڂ̃N�H�[�^�j�I��
	//! @return XMFLOAT4 ���ʂ̃N�H�[�^�j�I��
	//!
	static XMFLOAT4 CalcQuaternionMultiply(const XMFLOAT4& target1 , const XMFLOAT4& target2);


	//!
	//! @brief �s�񓯎m�̏�Z
	//! @param[in] target1 ��Z����1�ڂ̍s��
	//! @param[in] target2 ��Z����2�ڂ̍s��
	//! @param[out] result ���ʂ̍s��
	//! @return const XMFLOAT4X4& ���ʂ̍s��
	//!
	static const XMFLOAT4X4& CalcMatrixMultply(const XMFLOAT4X4& target1 , const XMFLOAT4X4& target2 , XMFLOAT4X4& result);

	//!
	//! @brief �s�񓯎m�̏�Z
	//! @param[in] target1 ��Z����1�ڂ̍s��
	//! @param[in] target2 ��Z����2�ڂ̍s��
	//! @return XMFLOAT4X4 ���ʂ̍s��
	//!
	static XMFLOAT4X4 CalcMatrixMultply(const XMFLOAT4X4& target1 , const XMFLOAT4X4& target2);

	//!
	//! @brief Float3���m�̉��Z
	//! @param[in] target1 ���Z����1�ڂ�Float3
	//! @param[in] target2 ���Z����2�ڂ�Float3
	//! @param[out] result ���ʂ�Float3
	//! @return const XMFLOAT3& ���ʂ�Float3
	//!
	static const XMFLOAT3& CalcFloat3Addition(const XMFLOAT3& target1 , const XMFLOAT3& target2 , XMFLOAT3& result);

	//!
	//! @brief Float3���m�̉��Z
	//! @param[in] target1 ���Z����1�ڂ�Float3
	//! @param[in] target2 ���Z����2�ڂ�Float3
	//! @return XMFLOAT3 ���ʂ�Float3
	//!
	static XMFLOAT3 CalcFloat3Addition(const XMFLOAT3& target1 , const XMFLOAT3& target2);

	//!
	//! @brief Float3���m�̌��Z
	//! @param[in] target1 ���Z����1�ڂ�Float3
	//! @param[in] target2 ���Z����2�ڂ�Float3
	//! @param[out] result ���ʂ�Float3
	//! @return const XMFLOAT3& ���ʂ�Float3
	//!
	static const XMFLOAT3& CalcFloat3Subtraction(const XMFLOAT3& target1 , const XMFLOAT3& target2 , XMFLOAT3& result);

	//!
	//! @brief Float3���m�̌��Z
	//! @param[in] target1 ���Z����1�ڂ�Float3
	//! @param[in] target2 ���Z����2�ڂ�Float3
	//! @return XMFLOAT3 ���ʂ�Float3
	//!
	static XMFLOAT3 CalcFloat3Subtraction(const XMFLOAT3& target1 , const XMFLOAT3& target2);

	//!
	//! @brief �n�_����I�_�ւ̃x�N�g�����Z�o
	//! @details Float3���m�̌��Z�Ƃ��܂�ς��Ȃ�
	//! @param[in] start �n�_�̃��P�[�V����
	//! @param[in] end �I�_�̃��P�[�V����
	//! @param[out] result ���ʂ�Float3
	//! @return const XMFLOAT3& ���ʂ�Float3
	//!
	static const XMFLOAT3& CalcFloat3FromStartToEnd(const XMFLOAT3& start , const XMFLOAT3& end , XMFLOAT3& result);

	//!
	//! @brief �n�_����I�_�ւ̃x�N�g�����Z�o
	//! @details Float3���m�̌��Z�Ƃ��܂�ς��Ȃ�
	//! @param[in] start �n�_�̃��P�[�V����
	//! @param[in] end �I�_�̃��P�[�V����
	//! @return XMFLOAT3 ���ʂ�Float3
	//!
	static XMFLOAT3 CalcFloat3FromStartToEnd(const XMFLOAT3& start , const XMFLOAT3& end);

	//!
	//! @brief Float3�̒������Z�o
	//! @param[in] target �������擾����Float3
	//! @param[out] result ���ʂ�Float3
	//! @return const XMFLOAT3& ���ʂ�Float3
	//!
	static const float& CalcFloat3Length(const XMFLOAT3& target , float& result);

	//!
	//! @brief Float3�̒������Z�o
	//! @param[in] target �������擾����Float3
	//! @return XMFLOAT3 ���ʂ�Float3
	//!
	static float CalcFloat3Length(const XMFLOAT3& target);

	//!
	//! @brief Float3�̐��K���������̂��Z�o
	//! @param[in] target ���K������Float3
	//! @param[out] result ���ʂ�Float3
	//! @return const XMFLOAT3& ���ʂ�Float3
	//!
	static const XMFLOAT3& CalcFloat3Normalize(const XMFLOAT3& target , XMFLOAT3& result);

	//!
	//! @brief Float3�̐��K���������̂��Z�o
	//! @param[in] target ���K������Float3
	//! @return XMFLOAT3 ���ʂ�Float3
	//!
	static XMFLOAT3 CalcFloat3Normalize(const XMFLOAT3& target);

	//!
	//! @brief Float3�̓���
	//! @param[in] target1 ���ς���1�ڂ�Float3
	//! @param[in] target2 ���ς���2�ڂ�Float3
	//! @param[out] result ���ʂ�Float3
	//! @return const XMFLOAT3& ���ʂ�Float3
	//!
	static const float& CalcFloat3Dot(const XMFLOAT3& target1 , const XMFLOAT3& target2 , float& result);

	//!
	//! @brief Float3�̓���
	//! @param[in] target1 ���ς���1�ڂ�Float3
	//! @param[in] target2 ���ς���2�ڂ�Float3
	//! @return XMFLOAT3 ���ʂ�Float3
	//!
	static float CalcFloat3Dot(const XMFLOAT3& target1 , const XMFLOAT3& target2);

	//!
	//! @brief Float3�̊O��
	//! @param[in] target1 �O�ς���1�ڂ�Float3
	//! @param[in] target2 �O�ς���2�ڂ�Float3
	//! @param[out] result ���ʂ�Float3
	//! @return const XMFLOAT3& ���ʂ�Float3
	//!
	static const XMFLOAT3& CalcFloat3Cross(const XMFLOAT3& target1 , const XMFLOAT3& target2 , XMFLOAT3& result);

	//!
	//! @brief Float3�̊O��
	//! @param[in] target1 �O�ς���1�ڂ�Float3
	//! @param[in] target2 �O�ς���2�ڂ�Float3
	//! @return XMFLOAT3 ���ʂ�Float3
	//!
	static XMFLOAT3 CalcFloat3Cross(const XMFLOAT3& target1 , const XMFLOAT3& target2);

	//!
	//! @brief Float3�̃X�J���[��
	//! @param[in] target �X�J���[�ς���Float3
	//! @param[in] scalar �X�J���[�l
	//! @param[out] result ���ʂ�Float3
	//! @return const XMFLOAT3& ���ʂ�Float3
	//!
	static const XMFLOAT3& CalcFloat3Scalar(const XMFLOAT3& target , const float& scalar , XMFLOAT3& result);

	//!
	//! @brief Float3�̃X�J���[��
	//! @param[in] target �X�J���[�ς���Float3
	//! @param[in] scalar �X�J���[�l
	//! @return XMFLOAT3 ���ʂ�Float3
	//!
	static XMFLOAT3 CalcFloat3Scalar(const XMFLOAT3& target , const float& scalar);

	//!
	//! @brief Float3���s��Ə�Z
	//! @param[in] target ��Z����Float3
	//! @param[in] mtx ��Z����s��
	//! @param[out] result ���ʂ�Float3
	//! @return const XMFLOAT3& ���ʂ�Float3
	//!
	static const XMFLOAT3& CalcFloat3MultplyMatrix(const XMFLOAT3& target , const XMFLOAT4X4& mtx , XMFLOAT3& result);

	//!
	//! @brief Float3���s��Ə�Z
	//! @param[in] target ��Z����Float3
	//! @param[in] mtx ��Z����s��
	//! @return XMFLOAT3 ���ʂ�Float3
	//!
	static XMFLOAT3 CalcFloat3MultplyMatrix(const XMFLOAT3& target , const XMFLOAT4X4& mtx);

	//!
	//! @brief Float3�z�񂩂�ŏ��ő�l���Z�o
	//! @param[in] target �Ώۂ̔z��
	//! @param[out] resultMin ���ʂ̍ŏ��l
	//! @param[out] resultMax ���ʂ̍ő�l
	//!
	static const void CalcFloat3MinMax(const std::vector<XMFLOAT3>& target , XMFLOAT3& resultMin , XMFLOAT3& resultMax);

	//!
	//! @brief Float�̐��`���
	//! @param[in] start �J�n
	//! @param[in] end �I��
	//! @param[in] alpha �A���t�@�l
	//! @param[out] result ���ʂ�Float
	//! @return const float& ���ʂ�Float
	//!
	static const float& Lerp(const float& start , const float& end , const float& alpha , float& result);

	//!
	//! @brief Float�̐��`���
	//! @param[in] start �J�n
	//! @param[in] end �I��
	//! @param[in] alpha �A���t�@�l
	//! @return float ���ʂ�Float
	//!
	static float Lerp(const float& start , const float& end , const float& alpha);

	//!
	//! @brief Float3�̐��`���
	//! @param[in] start �J�n
	//! @param[in] end �I��
	//! @param[in] alpha �A���t�@�l
	//! @param[out] result ���ʂ�Float3
	//! @return const XMFLOAT3& ���ʂ�Float3
	//!
	static const XMFLOAT3& Lerp(const XMFLOAT3& start , const XMFLOAT3& end , const float& alpha , XMFLOAT3& result);

	//!
	//! @brief Float3�̐��`���
	//! @param[in] start �J�n
	//! @param[in] end �I��
	//! @param[in] alpha �A���t�@�l
	//! @return XMFLOAT3 ���ʂ�Float3
	//!
	static XMFLOAT3 Lerp(const XMFLOAT3& start , const XMFLOAT3& end , const float& alpha);

	//!
	//! @brief Float4�̐��`���
	//! @param[in] start �J�n
	//! @param[in] end �I��
	//! @param[in] alpha �A���t�@�l
	//! @param[out] result ���ʂ�Float4
	//! @return const XMFLOAT4& ���ʂ�Float4
	//!
	static const XMFLOAT4& Lerp(const XMFLOAT4& start , const XMFLOAT4& end , const float& alpha , XMFLOAT4& result);

	//!
	//! @brief Float4�̐��`���
	//! @param[in] start �J�n
	//! @param[in] end �I��
	//! @param[in] alpha �A���t�@�l
	//! @return XMFLOAT4 ���ʂ�Float4
	//!
	static XMFLOAT4 Lerp(const XMFLOAT4& start , const XMFLOAT4& end , const float& alpha);

	//!
	//! @brief Float4X4�i�s��j�̐��`���
	//! @param[in] start �J�n
	//! @param[in] end �I��
	//! @param[in] alpha �A���t�@�l
	//! @param[out] result ���ʂ�Float4X4
	//! @return const XMFLOAT4X4& ���ʂ�Float4X4
	//!
	static const XMFLOAT4X4& Lerp(const XMFLOAT4X4& start , const XMFLOAT4X4& end , const float& alpha , XMFLOAT4X4& result);

	//!
	//! @brief Float4X4�i�s��j�̐��`���
	//! @param[in] start �J�n
	//! @param[in] end �I��
	//! @param[in] alpha �A���t�@�l
	//! @return XMFLOAT4X4 ���ʂ�Float4X4
	//!
	static XMFLOAT4X4 Lerp(const XMFLOAT4X4& start , const XMFLOAT4X4& end , const float& alpha);
};