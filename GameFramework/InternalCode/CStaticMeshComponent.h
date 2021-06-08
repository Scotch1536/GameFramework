#pragma once
#include "ModelData.h"
#include "CTransform.h"
#include "IRender.h"
#include "CRenderComponent.h"

class CStaticMeshComponent :public CComponent , public IRender
{
private:
	ModelData* mModel;							//���f���f�[�^
	CTransform mTransform;						//�g�����X�t�H�[��
	CRenderComponent& mRenderComponent;			//�����_�[�R���|�[�l���g
public:
	CStaticMeshComponent(IActor& owner , ModelData& model);

	//���f���̃Z�b�g
	void SetModel(ModelData& model)
	{
		mModel = &model;
	}

	//�`��
	void Render()override;
};