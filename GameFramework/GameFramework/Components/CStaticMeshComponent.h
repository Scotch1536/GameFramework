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
	CModelData& mModel;							//���f���f�[�^
	CRenderComponent& mRenderComponent;			//�����_�[�R���|�[�l���g

public:
	CTransform Transform;			//�g�����X�t�H�[��

	CStaticMeshComponent(CActor& owner , CTransform& parentTrans , CModelData& model , std::string vertexShaderPath , std::string pixelShaderPath , int priority = 90);

	//���f���̃Z�b�g
	void SetModel(CModelData& model)
	{
		mModel = model;
	}

	const CModelData& GetModel()
	{
		return mModel;
	}

	void Update()override;

	void Render()override;
};