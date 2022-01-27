//!
//! @file
//! @brief �{�b�N�X���b�V���R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <vector>

#include "CPrimitiveMeshComponent.h"

class CBoxMeshComponent :public CPrimitiveMeshComponent<>
{
private:
	XMFLOAT3 mMin , mMax;		//!< ���_�ƒ��_�Ƃ̊Ԃ̒����̍ŏ��ő�l

	//! @brief ���_�f�[�^�쐬
	void CreateVertexData()override;

	//! @brief �C���f�b�N�X�f�[�^�쐬
	void CreateIndexData()override;

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�����L����A�N�^�[
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] color �F���
	//! @param[in] min �ŏ��l
	//! @param[in] max �ő�l
	//! @param[in] vertexShaderPath ���_�V�F�[�_�̃p�X
	//! @param[in] pixelShaderPath �s�N�Z���V�F�[�_�̃p�X
	//!
	CBoxMeshComponent(CActor& owner , CTransform& parentTrans ,const XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f } ,
		XMFLOAT3 min = { -0.5f,-0.5f,-0.5f } , XMFLOAT3 max = { 0.5f,0.5f,0.5f } ,
		std::string vertexShaderPath = "Shader/vsnotex.hlsl" , std::string pixelShaderPath = "Shader/psnotex.hlsl");
};