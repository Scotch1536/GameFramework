#include "../Actor/CActor.h"
#include "../Transform/CTransform.h"
#include "../ExternalCode/dx11mathutil.h"

#include "CCameraComponent.h"
#include "CSpringArmComponent.h"

CSpringArmComponent::CSpringArmComponent(CActor& owner , const CTransform& parentTrans , CCameraComponent& useCamera , ESyncMode syncMode , int priority)
	:CComponent(owner , priority) ,
	mSyncMode(syncMode) ,
	mParentTransform(parentTrans) ,
	mUseCamera(useCamera)
{
	//�J�����R���|�[�l���g�ɃX�v�����O�A�[�����q�������Ƃ�ʒm
	mUseCamera.JoinSpringArm(*this);

	DX11MtxIdentity(mLocalMatrix);
}

void CSpringArmComponent::UpdateLocalMatrix()
{
	XMFLOAT3 eye = mUseCamera.GetEye();
	XMFLOAT3 lockAt = mUseCamera.GetLookat();
	XMFLOAT3 up = mUseCamera.GetUp();

	mLocalMatrix._11 = eye.x;
	mLocalMatrix._12 = eye.y;
	mLocalMatrix._13 = eye.z;
	mLocalMatrix._14 = 1;

	mLocalMatrix._21 = up.x - eye.x;
	mLocalMatrix._22 = up.y - eye.y;
	mLocalMatrix._23 = up.z - eye.z;
	mLocalMatrix._24 = 0;

	mLocalMatrix._31 = lockAt.x;
	mLocalMatrix._32 = lockAt.y;
	mLocalMatrix._33 = lockAt.z;
	mLocalMatrix._34 = 1;

	mLocalMatrix._41 = 0;
	mLocalMatrix._42 = 0;
	mLocalMatrix._43 = 0;
	mLocalMatrix._44 = 0;
}

void CSpringArmComponent::Update()
{
	if(mUseCamera.GetShouldUpdateViewMatrix())UpdateLocalMatrix();

	XMFLOAT4X4 cameraWorld;

	DX11MtxMultiply(cameraWorld , mLocalMatrix , mParentTransform.GetWorldMatrixResult());

	if(mSyncMode == ESyncMode::ALL_SYNC)
	{
		mUseCamera.SetEye({ cameraWorld._11,cameraWorld._12,cameraWorld._13 });
		mUseCamera.SetLookat({ cameraWorld._31,cameraWorld._32,cameraWorld._33 });
		mUseCamera.SetUp({ cameraWorld._21,cameraWorld._22,cameraWorld._23 });
	}
	else if(mSyncMode == ESyncMode::LOCATION_ONLY_SYNC)
	{
		XMFLOAT3 pLoc = mParentTransform.Location;
		mUseCamera.SetEye({ pLoc.x + mLocalMatrix._11,pLoc.y + mLocalMatrix._12 , pLoc.z + mLocalMatrix._13 });
		mUseCamera.SetLookat({ pLoc.x,pLoc.y,pLoc.z });
	}
}