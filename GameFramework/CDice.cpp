#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CLightComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Components/CAABBColliderComponent.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Managers/CGameManager.h"
#include "GameFramework/Transform/CRotator.h"

#include "CDice.h"

CDice::CDice(CLevel& owner, XMFLOAT3& pointLocation) :CActor(owner, false), mPoint(pointLocation)
{
	CStaticMeshComponent& staticMesh = *new CStaticMeshComponent(*this, Transform,
		CModelDataManager::GetInstance().GetModel("./Assets/Models/dice/PlayerBox.x", "Assets/Models/dice/"),
		"Shader/vs.hlsl", "Shader/ps.hlsl");

	CSphereColliderComponent* sphereCllider = new CSphereColliderComponent(*this, staticMesh.GetModel(), Transform);
	//タグ追加
	AddTag("Dice");
	mStartQua = Transform.Rotation.GetQuaternion();
}

void CDice::Move()
{
	XMFLOAT3 fv = Transform.GetForwardVector();

	Transform.Location.x += fv.x * 1.25;
	Transform.Location.y += fv.y * 1.25;
	Transform.Location.z += fv.z * 1.25;
}

void CDice::Tick()
{
	Move();
	Transform.Rotation.ChangeAngleAndQuaternionToLocation(mPoint);
	/*if (mGoalQua == nullptr)
	{
		mGoalQua.reset(new XMFLOAT4);
		Transform.Rotation.CalcQuaternionToLocation(mPoint, *mGoalQua);
		mAlpha = 0.0f;
	}
	if (mGoalQua != nullptr)
	{
		bool isEnd = false;
		XMFLOAT4 result;

		mAlpha += mIncrementAlpha;
		if (mAlpha > 1.0f)
		{
			mAlpha = 1.0f;
			isEnd = true;
		}

		LCMath::Lerp(mStartQua, *mGoalQua, mAlpha, result);
		Transform.Rotation.SetQuaternion(result);

		if (isEnd)
		{
			mGoalQua.reset();
		}
	}*/


}
