#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

#include "VertexProto.h"

using Microsoft::WRL::ComPtr;

class CModelMeshData
{
private:
	ComPtr<ID3D11Buffer>  mVertexBuffer;					// ���_�o�b�t�@
	ComPtr<ID3D11Buffer>  mIndexBuffer;						// �C���f�b�N�X�o�b�t�@
	ComPtr<ID3D11Buffer>  mConstantBufferMaterial;			// �}�e���A���p�R���X�^���g�o�b�t�@

public:
	std::vector<SVertexUV> Vertices;			// ���_�f�[�^
	std::vector<unsigned int> Indices;			// �C���f�b�N�X
	std::vector<STexture> Textures;				// �e�N�X�`��
	SMaterial Material;							// �}�e���A��

	CModelMeshData() = default;
	CModelMeshData(std::vector<SVertexUV> vertices , std::vector<unsigned int> indices , std::vector<STexture> textures , SMaterial mtrl);

	bool SetupMesh();

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