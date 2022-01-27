//!
//! @file
//! @brief �X�^�e�B�b�N���b�V���R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <string>

#include "../Interfaces/IRender.h"
#include "../Transform/CTransform.h"
#include "../Data/CModelData.h"

#include "CComponent.h"

class CModelData;
class CRenderComponent;

//! @brief �X�^�e�B�b�N���b�V���R���|�[�l���g�N���X
class CStaticMeshComponent :public CComponent , public IRender
{
private:
	CModelData* mModel;							//!< ���f���f�[�^
	CRenderComponent& mRenderComponent;			//!< �����_�[�R���|�[�l���g

	//! @brief �X�V
	void Update()override;

	//! @brief �`��
	void Render()override;

public:
	CTransform Transform;			//!< �g�����X�t�H�[��

	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�����L����A�N�^�[
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] model ���f���f�[�^
	//! @param[in] vertexShaderPath ���_�V�F�[�_�̃p�X
	//! @param[in] pixelShaderPath �s�N�Z���V�F�[�_�̃p�X
	//!
	CStaticMeshComponent(CActor& owner , CTransform& parentTrans , CModelData& model , std::string vertexShaderPath , std::string pixelShaderPath);

	void SetModel(CModelData& model)
	{
		mModel = &model;
	}

	const CModelData& GetModel()
	{
		return *mModel;
	}

};