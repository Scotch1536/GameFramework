//!
//!	@file
//!	@brief トランスフォームシステムのソースファイル
//!

#include "../ExternalCode/DX11Settransform.h"
#include "../Managers/CGameManager.h"
#include "../Library/LCMath.h"
#include "../Actor/CActor.h"
#include "../Components/CLineComponent.h"

#include "CTransform.h"

CTransform::CTransform(IActor& partner):Rotation(*this) , mOwnerInterface(partner)
{
	LCMath::IdentityMatrix(mLocalMatrix);
	LCMath::IdentityMatrix(mWorldMatrix);
}

CTransform::CTransform(IActor& partner , CTransform& parentTrans): CTransform(partner)
{
	parentTrans.AttachTransform(*this);
}

CTransform::~CTransform()
{
	//親がいるなら自分を切り離す
	if(mParentTransform != nullptr)mParentTransform->DetachTransform(*this);

	//存在するなら
	if(mChildTransform.size() != 0)
	{
		for(auto& child : mChildTransform)
		{
			//子に自分をデタッチさせる
			child->DetachTransform(*this);
		}
	}
}

void CTransform::RequestDebugLine()
{
#ifdef _DEBUG
	if(!mDoDrawDebugLine)
	{
		mDoDrawDebugLine = true;

		//ラインコンポーネント作成
		new CLineComponent(mOwnerInterface.GetActor() , { 0.0f,0.0f,0.0f } , { 1.0f , 0.0f , 0.0f } , 50.0f , { 1.0f,0.0f,0.0f,1.0f } , this);
		new CLineComponent(mOwnerInterface.GetActor() , { 0.0f,0.0f,0.0f } , { 0.0f , 1.0f , 0.0f } , 50.0f , { 0.0f,1.0f,0.0f,1.0f } , this);
		new CLineComponent(mOwnerInterface.GetActor() , { 0.0f,0.0f,0.0f } , { 0.0f , 0.0f , 1.0f } , 50.0f , { 0.0f,0.0f,1.0f,1.0f } , this);
	}
#endif
}

void CTransform::AttachTransform(CTransform& attachTarget)
{
	//今から子になるトランスフォームのワールド変換行列を親との相対行列に変換
	XMFLOAT4X4 attachTargetMTX = attachTarget.GetWorldMatrix();
	XMFLOAT4X4 parentInvMTX = LCMath::InverseMatrix(mWorldMatrix);
	LCMath::CalcMatrixMultply(attachTargetMTX , parentInvMTX , attachTargetMTX);

	//今から子になるトランスフォームに相対行列をセット
	attachTarget.SetLocalMatrix(attachTargetMTX);

	attachTarget.mParentTransform = this;
	attachTarget.mIsChild = true;

	mChildTransform.emplace_back(&attachTarget);
}

void CTransform::DetachTransform(CTransform& detachTarget)
{
	//親と一致するなら
	if(mParentTransform == &detachTarget)
	{
		mLocalMatrix = mWorldMatrix;

		mParentTransform = nullptr;
		mIsChild = false;
	}

	//存在するなら
	if(mChildTransform.size() != 0)
	{
		for(auto itr = mChildTransform.begin(); itr != mChildTransform.end(); ++itr)
		{
			if((*itr) == &detachTarget)
			{
				mChildTransform.erase(itr);
				mChildTransform.shrink_to_fit();
				break;
			}
		}
	}
}

void CTransform::SetLocalMatrix(const XMFLOAT4X4& matrix)
{
	mLocalMatrix = matrix;

	Location.x = mLocalMatrix._41;
	Location.y = mLocalMatrix._42;
	Location.z = mLocalMatrix._43;

	Scale.x = LCMath::CalcFloat3Length({ mLocalMatrix._11,mLocalMatrix._12,mLocalMatrix._13 });
	Scale.y = LCMath::CalcFloat3Length({ mLocalMatrix._21,mLocalMatrix._22,mLocalMatrix._23 });
	Scale.z = LCMath::CalcFloat3Length({ mLocalMatrix._31,mLocalMatrix._32,mLocalMatrix._33 });

	mIgnoreUpdateMatrixOnce = true;
}

void CTransform::Update()
{
	//ローテーター更新
	Rotation.Update();

	//ロケーション、スケール、ローテーターどれか一つでも前フレームの情報と違えば
	if(!LCMath::CompareFloat3(Location , mLastFrameLocation) || !LCMath::CompareFloat3(Scale , mLastFrameScale) || !Rotation.GetIsSameQuaternionToBeforeFrame())
	{
		if(!mIgnoreUpdateMatrixOnce)
		{
			mShouldUpdateMatrix = true;
		}
		else
		{
			mIgnoreUpdateMatrixOnce = false;
		}

		mLastFrameLocation = Location;
		mLastFrameScale = Scale;
	}

	if(mShouldUpdateMatrix)
	{
		mShouldUpdateMatrix = false;

		//行列更新
		LCMath::CreateMatrix(Location , Scale , Rotation.GenerateMatrix() , mLocalMatrix);

		//存在するなら
		if(mEventsWhenMatrixUpdate.size() > 0)
		{
			//行列更新時実行イベントを行う
			for(auto& event : mEventsWhenMatrixUpdate)
			{
				event();
			}
		}
	}

	//親がいるなら
	if(mParentTransform != nullptr)
	{
		//自身のローカル行列に親のワールド行列をかけて自身のワールド行列とする（親子付け処理を行う）
		LCMath::CalcMatrixMultply(mLocalMatrix , mParentTransform->GetWorldMatrix() , mWorldMatrix);

		//ロケーションのみのオプションなら
		if(mAttachOption == EAttachOption::LOCATION_ONLY)
		{
			//平行移動成分以外を元に戻す
			mWorldMatrix._11 = mLocalMatrix._11;
			mWorldMatrix._12 = mLocalMatrix._12;
			mWorldMatrix._13 = mLocalMatrix._13;
			mWorldMatrix._21 = mLocalMatrix._21;
			mWorldMatrix._22 = mLocalMatrix._22;
			mWorldMatrix._23 = mLocalMatrix._23;
			mWorldMatrix._31 = mLocalMatrix._31;
			mWorldMatrix._32 = mLocalMatrix._32;
			mWorldMatrix._33 = mLocalMatrix._33;
		}
	}
	else
	{
		mWorldMatrix = mLocalMatrix;
	}

	//ビルボードなら結果の行列に上書き処理
	if(mIsBillboard)
	{
		//現在描画担当のカメラのビュー行列を取得
		const XMFLOAT4X4* camera = CGameManager::GetInstance().GetCameraViewMatrix();

		//取得できていれば
		if(camera != nullptr)
		{
			XMFLOAT4X4 inverseCamera;
			XMFLOAT4X4 resultMTX;

			//ビュー行列の逆行列算出
			LCMath::InverseMatrix(*camera , inverseCamera);

			//ローカル行列に逆行列を乗算
			LCMath::CalcMatrixMultply(mLocalMatrix , inverseCamera , resultMTX);

			//回転成分のみ上書き
			mWorldMatrix._11 = resultMTX._11;
			mWorldMatrix._12 = resultMTX._12;
			mWorldMatrix._13 = resultMTX._13;

			mWorldMatrix._21 = resultMTX._21;
			mWorldMatrix._22 = resultMTX._22;
			mWorldMatrix._23 = resultMTX._23;

			mWorldMatrix._31 = resultMTX._31;
			mWorldMatrix._32 = resultMTX._32;
			mWorldMatrix._33 = resultMTX._33;
		}
	}

	//存在するなら子を更新
	if(mChildTransform.size() != 0)
	{
		for(auto& child : mChildTransform)
		{
			child->Update();
		}
	}
}

void CTransform::RequestSetMatrix()
{
	//GPUにワールド変換行列をセットする
	DX11SetTransform::GetInstance()->SetTransform(DX11SetTransform::TYPE::WORLD , mWorldMatrix);
}

XMFLOAT3 CTransform::GetWorldRightVector()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrix._11;
	result.y = mWorldMatrix._12;
	result.z = mWorldMatrix._13;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetWorldUpwardVector()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrix._21;
	result.y = mWorldMatrix._22;
	result.z = mWorldMatrix._23;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetWorldForwardVector()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrix._31;
	result.y = mWorldMatrix._32;
	result.z = mWorldMatrix._33;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetLocalRightVector()const
{
	XMFLOAT3 result;

	result.x = mLocalMatrix._11;
	result.y = mLocalMatrix._12;
	result.z = mLocalMatrix._13;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetLocalUpwardVector()const
{
	XMFLOAT3 result;

	result.x = mLocalMatrix._21;
	result.y = mLocalMatrix._22;
	result.z = mLocalMatrix._23;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetLocalForwardVector()const
{
	XMFLOAT3 result;

	result.x = mLocalMatrix._31;
	result.y = mLocalMatrix._32;
	result.z = mLocalMatrix._33;

	LCMath::CalcFloat3Normalize(result , result);

	return result;
}

XMFLOAT3 CTransform::GetWorldLocation()const
{
	XMFLOAT3 result;

	result.x = mWorldMatrix._41;
	result.y = mWorldMatrix._42;
	result.z = mWorldMatrix._43;

	return result;
}

XMFLOAT3 CTransform::GetWorldScale()const
{
	XMFLOAT3 result;

	if(mParentTransform != nullptr)
	{
		result = mParentTransform->GetWorldScale();

		result.x *= Scale.x;
		result.y *= Scale.y;
		result.z *= Scale.z;

		return result;
	}
	else return Scale;
}