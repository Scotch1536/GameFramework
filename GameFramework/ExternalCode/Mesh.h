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
	ComPtr<ID3D11Buffer>  m_VertexBuffer;		// 頂点バッファ
	ComPtr<ID3D11Buffer>  m_IndexBuffer;		// インデックスバッファ
	ComPtr<ID3D11Buffer>  m_cbmtrl;				// マテリアル用コンスタントバッファ

public:
	ComPtr<ID3D11ShaderResourceView> m_whitesrv;		// 真っ白ＳＲＶ
	ComPtr<ID3D11Resource> m_whiteres;					// 真っ白RES

	std::vector<Vertex> m_vertices;				// 頂点データ
	std::vector<unsigned int> m_indices;		// インデックス
	std::vector<Texture> m_textures;			// テクスチャ
	ID3D11Device* m_dev;						// デバイス	
	Material m_mtrl;							// マテリアル

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