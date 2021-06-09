#include "CRotator.h"
#include "CTransform.h"
#include "LCMath.h"
#include "dx11mathutil.h"

CRotator::CRotator()
{
	DX11QtIdentity(mQuaternion);
}

bool CRotator::Update()
{
	if(!LCMath::CompareFloat3(angle,mCompareAngle))
	{
		LCMath::TransformFromEulerAnglesToQuaternion(angle , mQuaternion);

		mCompareAngle = angle;

		mIsNowFrameCompareResult = false;
	}
	else
	{
		mIsNowFrameCompareResult = true;
	}

	//if(mToQuaternion != nullptr)
	//{
	//	DX11QtSlerp(*mFromQuaternion , *mToQuaternion , mAlpha , mQuaternion);

	//	LCMath::TransformFromQuaternionToEulerAngles(mQuaternion , mAngle);

	//	if(mIsLastUpdate)
	//	{
	//		mIsLastUpdate = false;

	//		mFromQuaternion.reset();
	//		mToQuaternion.reset();
	//	}

	//	mAlpha += mIncreaceAlpha;

	//	if(mAlpha >= 1.0f)
	//	{
	//		mAlpha = 1.f;
	//		mIsLastUpdate = true;
	//	}
	//	return true;
	//}
	return false;
}

//void CRotator::RequestSLerp(XMFLOAT3 angle , float lerpTime)
//{
//	if(mAlpha != 0.f)mAlpha = 0.f;
//	if(lerpTime <= 0)lerpTime = 0.1f;
//
//	mIncreaceAlpha = 1.f / (lerpTime * 60);
//
//	mFromQuaternion.reset(new XMFLOAT4);
//	mToQuaternion.reset(new XMFLOAT4);
//
//	*mFromQuaternion = mQuaternion;
//
//	LCMath::TransformFromEulerAnglesToQuaternion(angle , *mToQuaternion);
//}

XMFLOAT4X4 CRotator::GenerateMatrix(CTransform& partner)
{
	XMFLOAT4X4 ansMTX;

	//クォータニオンから行列を作成
	DX11MtxFromQt(ansMTX , mQuaternion);

	return ansMTX;
}