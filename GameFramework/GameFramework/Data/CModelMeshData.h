//!
//! @file
//! @brief モデルメッシュデータのヘッダーファイル
//!

#pragma once
#include <DirectXMath.h>
#include <d3d11.h>
#include <wrl/client.h>
#include <vector>

#include "MeshDataDefinition.h"

using Microsoft::WRL::ComPtr;

//! @brief モデルメッシュデータクラス
class CModelMeshData
{
private:
	ComPtr<ID3D11Buffer>  mVertexBuffer;					//!< 頂点バッファ
	ComPtr<ID3D11Buffer>  mIndexBuffer;						//!< インデックスバッファ
	ComPtr<ID3D11Buffer>  mConstantBufferMaterial;			//!< マテリアル用コンスタントバッファ

public:
	std::vector<SVertexUV> Vertices;			//!< 頂点
	std::vector<unsigned int> Indices;			//!< インデックス
	std::vector<STexture> Textures;				//!< テクスチャ
	SMaterial Material;							//!< マテリアル

	//! @brief コンストラクタ
	CModelMeshData() = default;

	//!
	//! @brief コンストラクタ
	//! @param[in] vertices 頂点データ
	//! @param[in] indices インデックスデータ
	//! @param[in] textures テクスチャデータ
	//! @param[in] material マテリアルデータ
	//!
	CModelMeshData(std::vector<SVertexUV> vertices , std::vector<unsigned int> indices , std::vector<STexture> textures , SMaterial material);

	//!//! @brief メッシュのセットアップ
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