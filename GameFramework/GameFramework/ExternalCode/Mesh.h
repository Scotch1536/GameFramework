#pragma once
#include <string>
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include <wrl/client.h>
#include "VertexProto.h"

using Microsoft::WRL::ComPtr;

class Mesh
{
private:
	ComPtr<ID3D11Buffer>  m_VertexBuffer;		// ���_�o�b�t�@
	ComPtr<ID3D11Buffer>  m_IndexBuffer;		// �C���f�b�N�X�o�b�t�@
	ComPtr<ID3D11Buffer>  m_cbmtrl;				// �}�e���A���p�R���X�^���g�o�b�t�@

public:
	std::vector<Vertex> m_vertices;				// ���_�f�[�^
	std::vector<unsigned int> m_indices;		// �C���f�b�N�X
	std::vector<Texture> m_textures;			// �e�N�X�`��
	ID3D11Device* m_dev;						// �f�o�C�X	
	Material m_mtrl;							// �}�e���A��

private:
	bool SetupMesh();

public:
	Mesh(std::vector<Vertex> vertices , std::vector<unsigned int> indices , std::vector<Texture> textures , Material mtrl);

	ID3D11Buffer* GetVertexBuffer()const
	{
		return m_VertexBuffer.Get();
	}
	
	ID3D11Buffer* GetIndexBuffer()const
	{
		return m_IndexBuffer.Get();
	}
	
	ID3D11Buffer* GetConstantBuffer()const
	{
		return m_cbmtrl.Get();
	}
};