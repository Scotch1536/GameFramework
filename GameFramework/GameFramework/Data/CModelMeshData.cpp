//!
//! @file
//! @brief モデルメッシュデータのソースファイル
//!

#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>
#include "memory.h"

#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/shader.h"

#include "MeshDataDefinition.h"
#include "CModelMeshData.h"

using namespace std;
using namespace DirectX;
using Microsoft::WRL::ComPtr;

CModelMeshData::CModelMeshData(vector<SVertexUV> vertices , vector<unsigned int> indices , vector<STexture> textures , SMaterial material):
	Vertices(vertices) , Indices(indices) , Textures(textures) , Material(material)
{
	//メッシュのセットアップ
	SetupMesh();
}

void CModelMeshData::SetupMesh()
{
	ID3D11Device* dev = CDirectXGraphics::GetInstance()->GetDXDevice();

	// 頂点バッファ生成
	bool sts = CreateVertexBufferWrite(dev , static_cast<unsigned int>(sizeof(SVertexUV)) ,
		static_cast<unsigned int>(Vertices.size()) , Vertices.data() , &mVertexBuffer);
	if(!sts)
	{
		MessageBox(nullptr , "メッシュのセットアップに失敗しました" , "Error" , MB_OK);
		return;
	}

	// インデックスバッファ生成
	sts = CreateIndexBuffer(dev , static_cast<unsigned int>(Indices.size()) , Indices.data() , &mIndexBuffer);
	if(!sts)
	{
		MessageBox(nullptr , "メッシュのセットアップに失敗しました" , "Error" , MB_OK);
		return;
	}

	// マテリアル用コンスタントバッファ生成
	sts = CreateConstantBufferWrite(dev , sizeof(SConstantBufferMaterial) , &mConstantBufferMaterial);
	if(!sts)
	{
		MessageBox(nullptr , "メッシュのセットアップに失敗しました" , "Error" , MB_OK);
		return;
	}

	ID3D11DeviceContext* devicecontext = CDirectXGraphics::GetInstance()->GetImmediateContext();;

	//定数バッファ初期化
	D3D11_MAPPED_SUBRESOURCE pData;

	SConstantBufferMaterial cb;

	cb.AmbientMaterial.w = 1.0f;
	cb.AmbientMaterial.x = Material.Ambient.x;
	cb.AmbientMaterial.y = Material.Ambient.y;
	cb.AmbientMaterial.z = Material.Ambient.z;

	cb.DiffuseMaterial.w = 1.0f;
	cb.DiffuseMaterial.x = Material.Diffuse.x;
	cb.DiffuseMaterial.y = Material.Diffuse.y;
	cb.DiffuseMaterial.z = Material.Diffuse.z;

	cb.SpecularMaterial.w = 1.0f;
	cb.SpecularMaterial.x = Material.Specular.x;
	cb.SpecularMaterial.y = Material.Specular.y;
	cb.SpecularMaterial.z = Material.Specular.z;

	HRESULT hr = devicecontext->Map(mConstantBufferMaterial.Get() , 0 , D3D11_MAP_WRITE_DISCARD , 0 , &pData);
	if(SUCCEEDED(hr))
	{
		memcpy_s(pData.pData , pData.RowPitch , (void*)(&cb) , sizeof(SConstantBufferMaterial));
		devicecontext->Unmap(mConstantBufferMaterial.Get() , 0);
	}
}
