#pragma once
#include <string>

#include "../ExternalCode/ModelData.h"
#include "../Interfaces/IRender.h"
#include "../Transform/CChildTransform.h"

#include "CComponent.h"

class CRenderComponent;

class CStaticMeshComponent :public CComponent , public IRender
{
private:
	CChildTransform mTransform;			//�g�����X�t�H�[��

	ModelData* mModel;							//���f���f�[�^
	CRenderComponent& mRenderComponent;			//�����_�[�R���|�[�l���g
public:
	CStaticMeshComponent(IActor& owner , ModelData& model , std::string vertexShaderPath , std::string pixelShaderPath , int priority = 90);

	//���f���̃Z�b�g
	void SetModel(ModelData& model)
	{
		mModel = &model;
	}

	//�`��
	void Render()override;
};