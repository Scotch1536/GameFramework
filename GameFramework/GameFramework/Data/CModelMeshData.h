//!
//! @file
//! @brief ���f�����b�V���f�[�^�̃w�b�_�[�t�@�C��
//!

#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

#include "MeshDataDefinition.h"

using Microsoft::WRL::ComPtr;

//! @brief ���f�����b�V���f�[�^�N���X
class CModelMeshData
{
private:
	ComPtr<ID3D11Buffer>  mVertexBuffer;					//!< ���_�o�b�t�@
	ComPtr<ID3D11Buffer>  mIndexBuffer;						//!< �C���f�b�N�X�o�b�t�@
	ComPtr<ID3D11Buffer>  mConstantBufferMaterial;			//!< �}�e���A���p�R���X�^���g�o�b�t�@

public:
	std::vector<SVertexUV> Vertices;			//!< ���_
	std::vector<unsigned int> Indices;			//!< �C���f�b�N�X
	std::vector<STexture> Textures;				//!< �e�N�X�`��
	SMaterial Material;							//!< �}�e���A��

	//! @brief �R���X�g���N�^
	CModelMeshData() = default;

	//!
	//! @brief �R���X�g���N�^
	//! @param[in] vertices ���_�f�[�^
	//! @param[in] indices �C���f�b�N�X�f�[�^
	//! @param[in] textures �e�N�X�`���f�[�^
	//! @param[in] material �}�e���A���f�[�^
	//!
	CModelMeshData(std::vector<SVertexUV> vertices , std::vector<unsigned int> indices , std::vector<STexture> textures , SMaterial material);

	//!//! @brief ���b�V���̃Z�b�g�A�b�v
	void SetupMesh();

	ID3D11Buffer* GetVertexBuffer()const
	{
		return mVertexBuffer.Get();
	}
	
	ID3D11Buffer* GetIndexBuffer()const
	{
		return mIndexBuffer.Get();
	}
	
	ID3D11Buffer* GetConstantBuffer()const
	{
		return mConstantBufferMaterial.Get();
	}
};