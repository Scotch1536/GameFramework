#pragma once
#include <string>

#include "../ExternalCode/ModelData.h"
#include "../Interfaces/IRender.h"
#include "../Transform/CTransform.h"

#include "CComponent.h"

class CRenderComponent;

class CStaticMeshComponent :public CComponent , public IRender
{
private:
	ModelData& mModel;							//モデルデータ
	CRenderComponent& mRenderComponent;			//レンダーコンポーネント

public:
	CTransform Transform;			//トランスフォーム

	CStaticMeshComponent(CActor& owner , ModelData& model , std::string vertexShaderPath , std::string pixelShaderPath , int priority = 90);

	//モデルのセット
	void SetModel(ModelData& model)
	{
		mModel = model;
	}

	const ModelData& GetModel()
	{
		return mModel;
	}

	//描画
	void Render()override;
};