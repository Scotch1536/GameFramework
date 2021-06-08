#include "CRotator.h"


void CRotator::Init()
{
	DX11QtIdentity(mQua);
}

void CRotator::Update()
{	
	if (mGoalQua != nullptr)
	{
		DX11QtSlerp(*mStartQua, *mGoalQua, mAlpha, mQua);
		
		if (mAlpha>1.0f)
		{
			mGoalQua.reset();
		}
		mAlpha++;
	}	
}

//void CRotator::Update()
//{
//	XMFLOAT3 nowPos{ 0.0f,0.0f,0.0f };
//
//	XMFLOAT4 mAxisX;
//	XMFLOAT4 mAxisY;
//	XMFLOAT4 mAxisZ;
//
//	//X�������o��
//	mAxisX.x = mMtx._11;
//	mAxisX.y = mMtx._12;
//	mAxisX.z = mMtx._13;
//	mAxisX.w = 0.0f;
//
//	//Y�������o��
//	mAxisY.x = mMtx._21;
//	mAxisY.y = mMtx._22;
//	mAxisY.z = mMtx._23;
//	mAxisY.w = 0.0f;
//
//	//Z�������o��
//	mAxisZ.x = mMtx._31;
//	mAxisZ.y = mMtx._32;
//	mAxisZ.z = mMtx._33;
//	mAxisZ.w = 0.0f;
//	
//	{
//		//�s�񂩂�N�I�[�^�j�I���𐶐�
//		DX11GetQtfromMatrix(mMtx, mQua);
//
//		XMFLOAT4 qtX, qtY, qtZ; //�N�I�[�^�j�I��
//
//		//�w�莲��]�̃N�I�[�^�j�I���𐶐�
//		DX11QtRotationAxis(qtX, mAxisX, mAngle.x);
//		DX11QtRotationAxis(qtY, mAxisY, mAngle.y);
//		DX11QtRotationAxis(qtZ, mAxisZ, mAngle.z);
//
//		//�N�I�[�^�j�I��������
//		XMFLOAT4 tempQt1;
//		DX11QtMul(tempQt1, mQua, qtX);
//
//		XMFLOAT4 tempQt2;
//		DX11QtMul(tempQt2, qtY, qtZ);
//
//		XMFLOAT4 tempQt3;
//		DX11QtMul(tempQt3, tempQt1, tempQt2);
//
//		//�N�I�[�^�j�I�����m�[�}���C�Y
//		DX11QtNormalize(tempQt3, tempQt3);
//
//		//�N�I�[�^�j�I������s����쐬
//		DX11MtxFromQt(mMtx, tempQt3);
//	}	
//	
//	mMtx._41 = nowPos.x;
//	mMtx._42 = nowPos.y;
//	mMtx._43 = nowPos.z;
//}

void CRotator::SetAngle(XMFLOAT3 angle,float time)
{
	mAngle = angle;
	mInc = 1 / (time * 60);
	mStartQua.reset();
	*mStartQua = mQua;
	mGoalQua.reset();
	EulerAnglesToQuaternion(mAngle, *mGoalQua);

}

XMFLOAT4X4 CRotator::GetMtx()
{
	//�N�H�[�^�j�I������s����쐬
	DX11MtxFromQt(mMtx, mQua);

	return mMtx;
}

void CRotator::EulerAnglesToQuaternion(XMFLOAT3 angle, XMFLOAT4 qua)
{	
	float cosRoll = cos(angle.x / 2.0f);
	float sinRoll = sin(angle.x / 2.0f);
	float cosPitch = cos(angle.y / 2.0f);
	float sinPitch = sin(angle.y / 2.0f);
	float cosYaw = cos(angle.z / 2.0f);
	float sinYaw = sin(angle.z / 2.0f);

	qua.x = cosRoll * cosPitch * cosYaw + sinRoll * sinPitch * sinYaw;
	qua.y = sinRoll * cosPitch * cosYaw - cosRoll * sinPitch * sinYaw;
	qua.z = cosRoll * sinPitch * cosYaw + sinRoll * cosPitch * sinYaw;
	qua.w = cosRoll * cosPitch * sinYaw - sinRoll * sinPitch * cosYaw;
}