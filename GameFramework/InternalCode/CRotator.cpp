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
//	//X軸を取り出す
//	mAxisX.x = mMtx._11;
//	mAxisX.y = mMtx._12;
//	mAxisX.z = mMtx._13;
//	mAxisX.w = 0.0f;
//
//	//Y軸を取り出す
//	mAxisY.x = mMtx._21;
//	mAxisY.y = mMtx._22;
//	mAxisY.z = mMtx._23;
//	mAxisY.w = 0.0f;
//
//	//Z軸を取り出す
//	mAxisZ.x = mMtx._31;
//	mAxisZ.y = mMtx._32;
//	mAxisZ.z = mMtx._33;
//	mAxisZ.w = 0.0f;
//	
//	{
//		//行列からクオータニオンを生成
//		DX11GetQtfromMatrix(mMtx, mQua);
//
//		XMFLOAT4 qtX, qtY, qtZ; //クオータニオン
//
//		//指定軸回転のクオータニオンを生成
//		DX11QtRotationAxis(qtX, mAxisX, mAngle.x);
//		DX11QtRotationAxis(qtY, mAxisY, mAngle.y);
//		DX11QtRotationAxis(qtZ, mAxisZ, mAngle.z);
//
//		//クオータニオンを合成
//		XMFLOAT4 tempQt1;
//		DX11QtMul(tempQt1, mQua, qtX);
//
//		XMFLOAT4 tempQt2;
//		DX11QtMul(tempQt2, qtY, qtZ);
//
//		XMFLOAT4 tempQt3;
//		DX11QtMul(tempQt3, tempQt1, tempQt2);
//
//		//クオータニオンをノーマライズ
//		DX11QtNormalize(tempQt3, tempQt3);
//
//		//クオータニオンから行列を作成
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
	//クォータニオンから行列を作成
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