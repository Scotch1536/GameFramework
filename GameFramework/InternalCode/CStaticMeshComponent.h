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
	CStaticMeshComponent(IActor& owner);

	//モデルのセット
	void SetModel(std::string filename , std::string resourcefolder);

	//描画
	void Render()override;
};