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
	ModelData& mModel;							//���f���f�[�^
	CRenderComponent& mRenderComponent;			//�����_�[�R���|�[�l���g

public:
	CTransform Transform;			//�g�����X�t�H�[��

	CStaticMeshComponent(CActor& owner , ModelData& model , std::string vertexShaderPath , std::string pixelShaderPath , int priority = 90);

	//���f���̃Z�b�g
	void SetModel(ModelData& model)
	{
		mModel = model;
	}

	const ModelData& GetModel()
	{
		return mModel;
	}

	//�`��
	void Render()override;
};