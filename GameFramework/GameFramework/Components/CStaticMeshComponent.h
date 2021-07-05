#pragma once
#include <string>

#include "../ExternalCode/CModelData.h"
#include "../Interfaces/IRender.h"
#include "../Transform/CTransform.h"

#include "CComponent.h"

class CRenderComponent;

class CStaticMeshComponent :public CComponent , public IRender
{
private:
	CModelData& mModel;							//���f���f�[�^
	CRenderComponent& mRenderComponent;			//�����_�[�R���|�[�l���g

public:
	CTransform Transform;			//�g�����X�t�H�[��

	CStaticMeshComponent(CActor& owner , CModelData& model , std::string vertexShaderPath , std::string pixelShaderPath , int priority = 90);

	//���f���̃Z�b�g
	void SetModel(CModelData& model)
	{
		mModel = model;
	}

	const CModelData& GetModel()
	{
		return mModel;
	}

	//�`��
	void Render()override;
};