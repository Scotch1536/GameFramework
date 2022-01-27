//!
//! @file
//! @brief �f�B�X�v���C2D�R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

#pragma once
#include "CPlaneMeshComponent.h"

//! @brief �f�B�X�v���C2D�R���|�[�l���g�N���X
class CDisplay2DComponent :public CPlaneMeshComponent<SVertex2D>
{
private:
	ID3D11ShaderResourceView* mTextureSRV = nullptr;		//!< �e�N�X�`��SRV

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
	//! @param[in] owner ���̃R���|�[�l���g�����L����A�N�^�[
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] texturePath �e�N�X�`���t�@�C���̃p�X
	//! @param[in] color �F���
	//! @param[in] vertexShaderPath ���_�V�F�[�_�̃p�X
	//! @param[in] pixelShaderPath �s�N�Z���V�F�[�_�̃p�X
	//!
	CDisplay2DComponent(CActor& owner , CTransform& parentTrans , std::string texturePath , const XMFLOAT4& color,
		std::string vertexShaderPath = "Shader/basicvs.hlsl" , std::string pixelShaderPath = "Shader/basicps.hlsl");

	//!
	//! @brief �R���X�g���N�^
	//! @details �e�N�X�`�����Ȃ��ꍇ�̃R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�����L����A�N�^�[
	//! @param[in] parentTrans �e�̃g�����X�t�H�[��
	//! @param[in] color �F���
	//! @param[in] vertexShaderPath ���_�V�F�[�_�̃p�X
	//! @param[in] pixelShaderPath �s�N�Z���V�F�[�_�̃p�X
	//!
	CDisplay2DComponent(CActor& owner , CTransform& parentTrans , const XMFLOAT4& color ,
		std::string vertexShaderPath = "Shader/basicvs.hlsl" , std::string pixelShaderPath = "Shader/basicps.hlsl");

	//!
	//! @brief UV���̎擾
	//! @details �A�j���[�V�����@�\��t���������ȂǂɎg�p���邱�Ƃ�z��
	//! @param[in] index ���_�z��̃C���f�b�N�X
	//!
	XMFLOAT2* GetUV(int index);

};