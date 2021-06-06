#pragma once
#include "ModelData.h"
#include "CTransform.h"
#include "CRenderComponent.h"

class CStaticMeshComponent :public CComponent , IRender
{
private:
	ModelData mModel;
	CTransform mTransform;
	CRenderComponent mRenderComponent;
public:
	CStaticMeshComponent(IActor& owner);

	void SetModel(std::string filename , std::string resourcefolder);
	void Update()override;
	void Render()override;
};