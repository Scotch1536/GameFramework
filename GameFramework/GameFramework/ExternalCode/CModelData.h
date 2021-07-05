#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>

#include "../ExternalLibrary/Assimp/assimp/include/assimp/scene.h"
#include "../ExternalLibrary/Assimp/assimp/include/assimp/Importer.hpp"

#include "CMeshData.h"
#include "CDirectxGraphics.h"
#include "AssimpScene.h"
#include "VertexProto.h"

class CModelDataManager;

class CModelData
{
private:
	AssimpScene mAssimpScene;		// assimp scene
	std::string mDirectory;			// テクスチャファイルの位置

	std::vector<CMeshData> mMeshes;				// メッシュの集合がモデル
	std::vector<STexture> mTexturesLoaded;		// 既にロードされているテクスチャ
	std::vector<SMaterial> mMaterials;			// マテリアル群

	// ノードを解析
	void ProcessNode(aiNode* node , const aiScene* scene);

	// メッシュを解析
	CMeshData ProcessMesh(aiMesh* mesh , const aiScene* scene , int meshidx);

	// マテリアルを読み込む
	void LoadMaterial();

	// マテリアルに対応したテクスチャを取得する
	std::vector<STexture> LoadMaterialTextures(
		aiMaterial * mat ,
		aiTextureType type ,
		std::string typeName ,
		const aiScene * scene);

	void TextureInit(STexture& target);

public:
	CModelData() = default;
	~CModelData();

	bool Load(std::string resourcefolder , std::string filename);

	void WriteData(const CModelDataManager& partner , std::fstream& file);
	void ReadData(const CModelDataManager& partner , std::fstream& file);
	void ReadDataInit(const CModelDataManager& partner);

	const std::vector<CMeshData>& GetMeshes()const
	{
		return mMeshes;
	}
};
