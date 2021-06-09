#pragma once
#include "CComponent.h"
#include "ModelData.h"
#include "IRender.h"

class CChildTransform;
class CRenderComponent;

class CStaticMeshComponent :public CComponent , public IRender
{
private:
	CChildTransform& mTransform;				//トランスフォーム

	ModelData* mModel;							//モデルデータ
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