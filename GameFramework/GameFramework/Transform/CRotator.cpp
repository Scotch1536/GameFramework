#include "../Math/LCMath.h"
#include "../ExternalCode/dx11mathutil.h"

#include "CRotator.h"
#include "CTransform.h"

CRotator::CRotator()
{
	DX11QtIdentity(mQuaternion);
}

bool CRotator::Update()
{
	if(!LCMath::CompareFloat3(Angle , mLastFrameAngle)||mIsFirstTimeToUpdate)
	{
		mIsFirstTimeToUpdate = false;

		LCMath::TransformFromEulerAnglesToQuaternion(Angle , mQuaternion);

		mLastFrameAngle = Angle;

		mIsSameAngle = false;
	}
	else
	{
		mIsSameAngle = true;
	}
	return false;
}

XMFLOAT4X4 CRotator::GenerateMatrix()
{
	XMFLOAT4X4 ansMTX;

	//クォータニオンから行列を作成
	DX11MtxFromQt(ansMTX , mQuaternion);

	return ansMTX;
}