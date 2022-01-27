//!
//! @file
//! @brief スプリングアームコンポーネントのソースファイル
//!

#include "../Actor/CActor.h"
#include "../Transform/CTransform.h"
#include "../Library/LCMath.h"

#include "CCameraComponent.h"
#include "CSpringArmComponent.h"

CSpringArmComponent::CSpringArmComponent(CActor& owner , const CTransform& targetTrans , CCameraComponent& partnerCamera , ELinkMode linkMode , int priority)
	:CComponent(owner , priority) ,
	mSyncMode(linkMode) ,
	mTargetTransform(targetTrans) ,
	mPartnerCamera(partnerCamera)
{
	//カメラコンポーネントにスプリングアームを繋げる
	mPartnerCamera.JoinSpringArm(*this);
}

void CSpringArmComponent::IncreaseAlpha()
{
	mAlpha += mIncrementAlpha;

	if(mAlpha > 1.0f)
	{
		mAlpha = 1.0f;
	}
}

void CSpringArmComponent::Update()
{
	XMFLOAT4X4 idealMatrix;

	if(mSyncMode == ELinkMode::ALL_LINK)
	{
		//パートナーカメラのカメラ座標変換行列のベースにターゲットのワールド変換行列を乗算することで親子関係を実現しその結果を理想の行列とする
		LCMath::CalcMatrixMultply(mPartnerCamera.GetCameraTransMatrixBase() , mTargetTransform.GetWorldMatrixResult() , idealMatrix);
	}
	else if(mSyncMode == ELinkMode::LOCATION_ONLY_LINK)
	{
		//パートナーカメラのカメラ座標変換行列のベースにターゲットのロケーションのみ加算する
		idealMatrix = mPartnerCamera.GetCameraTransMatrixBase();
		idealMatrix._41 += mTargetTransform.Location.x;
		idealMatrix._42 += mTargetTransform.Location.y;
		idealMatrix._43 += mTargetTransform.Location.z;
	}

	//理想の行列があるなら
	if(mIdealMatrix != nullptr)
	{
		//前回の理想の行列と今回の理想の行列が違うかつアルファ値がゼロ以外なら
		if(!LCMath::CompareMatrix(*mIdealMatrix , idealMatrix) && mAlpha != 0.0f)
		{
			//理想の行列の入れ替え
			mIdealMatrix.reset(new XMFLOAT4X4(idealMatrix));

			mAlpha = 0.0f;

			return;
		}
	}
	else
	{
		//理想の行列を設定
		mIdealMatrix.reset(new XMFLOAT4X4(idealMatrix));

		//理想の行列を新しいカメラ座標変換行列としてセットする
		mPartnerCamera.SetCameraTransMatrix(*mIdealMatrix);

		return;
	}

	//アルファ値の増加
	IncreaseAlpha();

	//現在のパートナーカメラのカメラ座標変換行列と理想の行列を線形補間しその結果を新しいカメラ座標変換行列としてセットする
	mPartnerCamera.SetCameraTransMatrix(LCMath::Lerp(mPartnerCamera.GetCameraTransMatrix() , *mIdealMatrix , mAlpha));
}