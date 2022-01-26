#pragma once
#include <vector>

#include "CPrimitiveMeshComponent.h"

//!
//! @file
//! @brief �X�t�B�A���b�V���R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

//! @brief �X�t�B�A���b�V���R���|�[�l���g�N���X
class CSphereMeshComponent :public CPrimitiveMeshComponent<>
{
private:
	float mRadius;				//!< ���a
	int mDivisionNumber;		//!< ������

	//! @brief ���_�f�[�^�쐬
	void CreateVertexData()override;

	//! @brief �C���f�b�N�X�f�[�^�쐬
	void CreateIndexData()override;

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�̏��L��
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] color �F���
	//! @param[in] divNum ������
	//! @param[in] radius ���a
	//! @param[in] vertexShaderPath ���_�V�F�[�_�̃p�X
	//! @param[in] pixelShaderPath �s�N�Z���V�F�[�_�̃p�X
	//!
	CSphereMeshComponent(CActor& owner , CTransform& parentTrans ,const XMFLOAT4& color = { 1.0f,1.0f,1.0f,1.0f } , int divNum = 50 , float radius = 0.5f ,
		std::string vertexShaderPath = "Shader/vsnotex.hlsl" , std::string pixelShaderPath = "Shader/psnotex.hlsl");
};