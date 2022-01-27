//!
//! @file
//! @brief ���ʃR���|�[�l���g�̃w�b�_�[�t�@�C��
//!

#pragma once
#include "CPrimitiveMeshComponent.h"

//! @brief ���ʃR���|�[�l���g�N���X
template<class VertexType = SVertexColor>
class CPlaneMeshComponent :public CPrimitiveMeshComponent<VertexType>
{
protected:
	//! @brief ���_�f�[�^�쐬
	void CreateVertexData()override;

	//! @brief �C���f�b�N�X�f�[�^�쐬
	void CreateIndexData()override;

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�����L����A�N�^�[
	//! @param[in] parentTans �e�̃g�����X�t�H�[��
	//! @param[in] color �F���
	//! @param[in] vertexShaderPath ���_�V�F�[�_�̃p�X
	//! @param[in] pixelShaderPath �s�N�Z���V�F�[�_�̃p�X
	//!
	CPlaneMeshComponent(CActor& owner , CTransform& parentTrans , const XMFLOAT4& color ,
		std::string vertexShaderPath = "Shader/vsnotex.hlsl" , std::string pixelShaderPath = "Shader/psnotex.hlsl" , bool isInit = true);

};