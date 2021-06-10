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
	float mAlpha;					//Slerp�Ŏg�p����A���t�@�l
	float mIncreaceAlpha;			//�A���t�@�̑����l

	XMFLOAT4 mQuaternion;							//�N�H�[�^�j�I���i���ݒn�j
	XMFLOAT3 mCompareAngle = { 0.f,0.f,0.f };		//��r���邽�߂̊p�x

	std::unique_ptr<XMFLOAT4> mFromQuaternion;			//�N�H�[�^�j�I���i�ړ��O�j
	std::unique_ptr<XMFLOAT4> mToQuaternion;			//�N�H�[�^�j�I���i�ړ���j

	bool mIsNowFrameCompareResult = true;
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

	const bool& GetIsNowCompareResult()const
	{
		return mIsNowFrameCompareResult;
	}

	void SetQuaternion(CChildTransform& partner , XMFLOAT4& qua)
	{
		mQuaternion = qua;
	}
};