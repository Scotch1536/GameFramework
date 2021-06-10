#pragma once
#include "CComponent.h"
#include "ModelData.h"
#include "IRender.h"
#include "CChildTransform.h"

class CRenderComponent;

class CStaticMeshComponent :public CComponent , public IRender
{
private:
	CChildTransform mTransform;				//�g�����X�t�H�[��

	ModelData* mModel;							//���f���f�[�^
	CRenderComponent& mRenderComponent;			//�����_�[�R���|�[�l���g
public:
	CStaticMeshComponent(IActor& owner , ModelData& model , int priority = 90);

	//���f���̃Z�b�g
	void SetModel(ModelData& model)
	{
		mModel = &model;
	}

	//�`��
	void Render()override;
};