//!
//! @file
//! @brief �����_�[�R���|�[�l���g�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <d3d11.h>
#include <wrl/client.h>

#include "../Data/MeshDataDefinition.h"

#include "CComponent.h"

using Microsoft::WRL::ComPtr;

//! @brief �����_�[�R���|�[�l���g�N���X
class CRenderComponent :public CComponent
{
private:
	ID3D11VertexShader* mVertexShader = nullptr;		//!< ���_�V�F�[�_�[
	ID3D11PixelShader* mPixelShader = nullptr;			//!< �s�N�Z���V�F�[�_�[
	ID3D11InputLayout* mVertexLayout = nullptr;			//!< ���_�t�H�[�}�b�g

public:
	//!
	//! @brief �R���X�g���N�^
	//! @param[in] owner ���̃R���|�[�l���g�����L����A�N�^�[
	//! @param[in] priority �D��x
	//!
	CRenderComponent(CActor& owner , int priority = 100);

	//!
	//! @brief ���_�V�F�[�_����
	//! @param[in] layout ���_�t�H�[�}�b�g
	//! @param[in] layoutSize ���_�t�H�[�}�b�g�̑傫��
	//! @param[in] vsFilePath ���_�V�F�[�_�̃p�X
	//!
	void GenerateVertexShader(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , std::string vsFilePath);

	//!
	//! @brief �s�N�Z���V�F�[�_����
	//! @param[in] psFilePath �s�N�Z���V�F�[�_�̃p�X
	//!
	void GeneratePixelShader(std::string psFilePath);

	//!
	//! @brief �s�N�Z���V�F�[�_����
	//! @param[in] stride �X�g���C�h�i���_�\���̂̃T�C�Y�j
	//! @param[in] indexSize �C���f�b�N�X�f�[�^�̃T�C�Y
	//! @param[in] shaderResourceView �V�F�[�_���\�[�X�r���[
	//! @param[in] vertexBuffer ���_�o�b�t�@
	//! @param[in] indexBuffer �C���f�b�N�X�o�b�t�@
	//! @param[in] materialCB �}�e���A���萔�o�b�t�@
	//!
	void Render(unsigned int stride,
		unsigned int indexSize ,
		ID3D11ShaderResourceView* shaderResourceView ,
		ID3D11Buffer* vertexBuffer ,
		ID3D11Buffer* indexBuffer ,
		ID3D11Buffer* materialCB);

};