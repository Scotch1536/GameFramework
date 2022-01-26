#pragma once
#include "CPlaneMeshComponent.h"

//!
//! @file
//! @brief �r���{�[�h�R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

//! @brief �r���{�[�h�R���|�[�l���g�N���X
class CBillboardComponent :public CPlaneMeshComponent<SVertexUV>
{
private:
	ID3D11ShaderResourceView* mTextureSRV;		//!< �e�N�X�`��SRV

	//!
	//! @brief ������
	//! @param[in] vertexShaderPath ���_�V�F�[�_�̃p�X
	//! @param[in] pixelShaderPath �s�N�Z���V�F�[�_�̃p�X
	//!
	void Init(std::string vertexShaderPath , std::string pixelShaderPath)override;

	//! @brief �X�V
	void Update()override;

	//! @brief �`��
	void Render()override;

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�̏��L��
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] texturePath �e�N�X�`���t�@�C���̃p�X
	//! @param[in] vertexShaderPath ���_�V�F�[�_�̃p�X
	//! @param[in] pixelShaderPath �s�N�Z���V�F�[�_�̃p�X
	//!
	CBillboardComponent(CActor& owner , CTransform& parentTrans , std::string texturePath ,
		std::string vertexShaderPath = "Shader/vs.hlsl" , std::string pixelShaderPath = "Shader/basicps.hlsl");

	XMFLOAT2* GetUV(int index)
	{
		return &mVertices.at(index).Tex;
	};

};