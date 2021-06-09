#pragma once
#include "CComponent.h"
#include "ModelData.h"
#include "IRender.h"
#include "CChildTransform.h"

class CRenderComponent;

class CStaticMeshComponent :public CComponent , public IRender
{
private:
	CChildTransform mTransform;				//トランスフォーム

	ModelData* mModel;							//モデルデータ
	CRenderComponent& mRenderComponent;			//レンダーコンポーネント
public:
	CStaticMeshComponent(IActor& owner , ModelData& model , int priority = 90);

	//モデルのセット
	void SetModel(ModelData& model)
	{
		mModel = &model;
	}

	//描画
	void Render()override;
};