//!
//! @file
//! @brief アタッチオブジェクトアクターのソースファイル
//!

#include <random>

#include "GameFramework/Components/CBoxMeshComponent.h"
#include "GameFramework/Components/CSphereMeshComponent.h"
#include "GameFramework/Components/CAABBColliderComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Managers/CSoundManager.h"

#include "CAttachObject.h"

CAttachObject::CAttachObject(ILevel& partner):CActor(partner)
{
	//乱数生成器作成
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<float> colorGenerator(0.0f , 1.0f);
	std::uniform_real_distribution<float> scaleGenerator(15.0f , 20.0f);

	//タグ追加
	AddTag("AttachObject");

	CColliderComponent* collider = nullptr;

	int randomNum = mt() % 2;

	if(randomNum == 0)
	{
		//ボックスメッシュコンポーネント追加&初期化
		CBoxMeshComponent& box = *new CBoxMeshComponent(*this , Transform , { colorGenerator(mt),colorGenerator(mt),colorGenerator(mt),1.0f });
		box.Transform.Scale = { scaleGenerator(mt),scaleGenerator(mt) ,scaleGenerator(mt) };
		mMesh = &box;

		//AABBコライダーコンポーネント追加
		collider = new CAABBColliderComponent(*this , mMesh->Transform);
	}
	else if(randomNum == 1)
	{
		//スフィアメッシュコンポーネント追加&初期化
		CSphereMeshComponent& sphere = *new CSphereMeshComponent(*this , Transform , { colorGenerator(mt),colorGenerator(mt),colorGenerator(mt),1.0f });
		sphere.Transform.Scale = { scaleGenerator(mt),scaleGenerator(mt) ,scaleGenerator(mt) };
		mMesh = &sphere;

		//スフィアコライダーコンポーネント追加
		collider = new CSphereColliderComponent(*this , mMesh->Transform);
	}

	collider->SetShouldUpdate(false);				//自身での更新をしなくする
	collider->SetObjectType("AttachObject");		//オブジェクトタイプセット

	//サウンド情報作成
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/attach.wav" , 0.1f , false , "Attach");
}

void CAttachObject::EventAtBeginCollide(CActor& collideActor)
{
	//当たったアクターが戦闘機なら
	if(collideActor.HasTag("Fighter"))
	{
		//戦闘機に自身をアタッチ
		collideActor.Transform.AttachTransform(Transform);

		//色変更
		XMFLOAT4 color = mMesh->GetColor();
		color.w = 0.5f;
		mMesh->SetColor(color);

		//アタッチサウンドを流す
		CSoundManager::GetInstance().PlaySound("Attach");

		//レベルに通知
		mOwnerInterface.Notice(*this);
	}
}