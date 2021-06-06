#include <string>
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include <unordered_map>
#include "memory.h"
#include "CDirectxGraphics.h"
#include "shader.h"
#include "vertexproto.h"
#include "Mesh.h"

using namespace std;
using namespace DirectX;
using Microsoft::WRL::ComPtr;

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures,Material mtrl){

	// 真っ白のSRVを一つ作っておく
	bool sts = CreateSRVfromFile("assets/white.bmp", CDirectXGraphics::GetInstance()->GetDXDevice() , CDirectXGraphics::GetInstance()->GetImmediateContext(), &m_whiteres,&m_whitesrv);
	if (!sts) {
		MessageBox(nullptr, "white,bmp load error", "error", MB_OK);
	}

	m_vertices = vertices;
	m_indices = indices;
	m_dev = CDirectXGraphics::GetInstance()->GetDXDevice();
	m_textures = textures;
	m_mtrl = mtrl;

	SetupMesh();
}

bool Mesh::SetupMesh()
{
	// 頂点バッファ生成
	bool sts = CreateVertexBufferWrite(m_dev,
		static_cast<unsigned int>(sizeof(Vertex)),			// ストライド
		static_cast<unsigned int>(m_vertices.size()),		// 頂点数
		m_vertices.data(),									// 頂点データ
		&m_VertexBuffer);
	if (!sts) {
		return false;
	}

	// インデックスバッファ生成
	sts = CreateIndexBuffer(m_dev,
		static_cast<unsigned int>(m_indices.size()),
		m_indices.data(),
		&m_IndexBuffer);
	if (!sts) {
		return false;
	}

	// マテリアル用コンスタントバッファ生成
	sts = CreateConstantBufferWrite(m_dev,
		sizeof(ConstantBufferMaterial),
		&m_cbmtrl);
	if (!sts) {
		return false;
	}

	ID3D11DeviceContext* devicecontext;
	devicecontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	// 定数バッファ更新
	D3D11_MAPPED_SUBRESOURCE pData;

	ConstantBufferMaterial cb;

	cb.AmbientMaterial.w = 1.0f;
	cb.AmbientMaterial.x = m_mtrl.m_Ambient.x;
	cb.AmbientMaterial.y = m_mtrl.m_Ambient.y;
	cb.AmbientMaterial.z = m_mtrl.m_Ambient.z;

	cb.DiffuseMaterial.w = 1.0f;
	cb.DiffuseMaterial.x = m_mtrl.m_Diffuse.x;
	cb.DiffuseMaterial.y = m_mtrl.m_Diffuse.y;
	cb.DiffuseMaterial.z = m_mtrl.m_Diffuse.z;

	cb.SpecularMaterial.w = 1.0f;
	cb.SpecularMaterial.x = m_mtrl.m_Specular.x;
	cb.SpecularMaterial.y = m_mtrl.m_Specular.y;
	cb.SpecularMaterial.z = m_mtrl.m_Specular.z;

	HRESULT hr = devicecontext->Map(m_cbmtrl.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
	if (SUCCEEDED(hr)) {
		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(ConstantBufferMaterial));
		devicecontext->Unmap(m_cbmtrl.Get(), 0);
	}

	return true;
}
