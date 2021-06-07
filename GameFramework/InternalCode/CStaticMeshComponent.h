#pragma once
#include "ModelData.h"
#include "CTransform.h"
#include "IRender.h"
#include "CRenderComponent.h"

class CStaticMeshComponent :public CComponent , public IRender
{
private:
	ModelData mModel;							//���f���f�[�^
	CTransform mTransform;						//�g�����X�t�H�[��
	CRenderComponent mRenderComponent;			//�����_�[�R���|�[�l���g
public:
	CStaticMeshComponent(IActor& owner);

	//���f���̃Z�b�g
	void SetModel(std::string filename , std::string resourcefolder);

	//�X�V
	void Update()override;

	//�`��
	void Render()override;
};