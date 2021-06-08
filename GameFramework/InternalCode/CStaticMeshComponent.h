#pragma once
#include "ModelData.h"
#include "CTransform.h"
#include "IRender.h"
#include "CRenderComponent.h"

class CStaticMeshComponent :public CComponent , public IRender
{
private:
	ModelData* mModel;							//モデルデータ
	CTransform mTransform;						//トランスフォーム
	CRenderComponent& mRenderComponent;			//レンダーコンポーネント
public:
	CStaticMeshComponent(IActor& owner , ModelData& model);

	//モデルのセット
	void SetModel(ModelData& model)
	{
		mModel = &model;
	}

	//描画
	void Render()override;
};