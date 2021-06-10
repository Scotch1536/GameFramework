#pragma once
#include "../ExternalCode/ModelData.h"
#include "../Interfaces/IRender.h"
#include "../Transform/CChildTransform.h"

#include "CComponent.h"

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