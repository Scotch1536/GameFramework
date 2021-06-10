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
	if(!LCMath::CompareFloat3(Angle,mCompareAngle))
	{
		LCMath::TransformFromEulerAnglesToQuaternion(Angle , mQuaternion);

		mCompareAngle = Angle;

		mIsNowFrameCompareResult = false;
	}
	else
	{
		mIsNowFrameCompareResult = true;
	}
	return false;
}

XMFLOAT4X4 CRotator::GenerateMatrix(CTransform& partner)
{
	XMFLOAT4X4 ansMTX;

	//クォータニオンから行列を作成
	DX11MtxFromQt(ansMTX , mQuaternion);

	return ansMTX;
}