#pragma once
#include <string>

#include "../Interfaces/IRender.h"
#include "../Transform/CTransform.h"
#include "../Data/CModelData.h"

#include "CComponent.h"

class CModelData;
class CRenderComponent;

class CStaticMeshComponent :public CComponent , public IRender
{
private:
	CModelData& mModel;							//モデルデータ
	CRenderComponent& mRenderComponent;			//レンダーコンポーネント

public:
	CTransform Transform;			//トランスフォーム

	CStaticMeshComponent(CActor& owner , CModelData& model , std::string vertexShaderPath , std::string pixelShaderPath , int priority = 90);

	//モデルのセット
	void SetModel(CModelData& model)
	{
		mModel = model;
	}

	const CModelData& GetModel()
	{
		return mModel;
	}

	//描画
	void Render()override;
};