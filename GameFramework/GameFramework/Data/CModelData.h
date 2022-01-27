//!
//! @file
//! @brief モデルデータのヘッダーファイル
//!

#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>

#include "../ExternalLibrary/Assimp/assimp/include/assimp/scene.h"
#include "../ExternalLibrary/Assimp/assimp/include/assimp/Importer.hpp"
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/AssimpScene.h"

#include "MeshDataDefinition.h"
#include "CModelMeshData.h"

class CModelDataManager;

//! @brief モデルデータクラス
class CModelData
{
private:
	AssimpScene mAssimpScene;					//!< Assimpシーン
	std::string mDirectory;						//!< テクスチャファイルのパス

	std::vector<CModelMeshData> mMeshes;		//!< メッシュ
	std::vector<STexture> mTexturesLoaded;		//!< 既にロードされているテクスチャ
	std::vector<SMaterial> mMaterials;			//!< マテリアル

	//!
	//! @brief ノード解析
	//! @param[in] node 解析するノード
	//! @param[in] scene シーン
	//!
	void ProcessNode(aiNode* node , const aiScene* scene);

	//!
	//! @brief メッシュ解析
	//! @param[in] mesh 解析するメッシュ
	//! @param[in] scene シーン
	//!
	CModelMeshData ProcessMesh(aiMesh* mesh , const aiScene* scene);

	//! @brief マテリアルのロード
	void LoadMaterial();

	//!
	//! @brief テクスチャのロード
	//! @param[in] mtrl マテリアル
	//! @param[in] type テクスチャタイプ
	//! @param[in] typeName テクスチャ名
	//! @param[in] scene シーン
	//! @return std::vector<STexture> 結果のテクスチャ
	//!
	std::vector<STexture> LoadTextures(aiMaterial* mtrl ,aiTextureType type ,std::string typeName ,const aiScene* scene);

	//!
	//! @brief テクスチャ初期化
	//! @param[in] target 初期化したいテクスチャ
	//!
	void TextureInit(STexture& target);

	//! @brief 読み込みデータ初期化
	void ReadDataInit();

public:
	//! @brief コンストラクタ
	CModelData() = default;

	//! @brief デストラクタ
	~CModelData();

	//!
	//! @brief モデルデータのロード
	//! @param[in] resourceFolderPath リソースフォルダのパス
	//! @param[in] filePath モデルファイルのパス
	//! @return bool ロードが成功したか
	//!
	bool Load(std::string resourceFolderPath , std::string filePath);

	//!
	//! @brief キャッシュデータの書き込み
	//! @param[in] partner モデルデータマネージャーの参照
	//! @param[in] file 書き込むファイル
	//!
	void WriteCacheData(const CModelDataManager& partner , std::fstream& file);

	//!
	//! @brief キャッシュデータの読み込み
	//! @param[in] partner モデルデータマネージャーの参照
	//! @param[in] file 読み込むファイル
	//!
	void ReadCacheData(const CModelDataManager& partner , std::fstream& file);

	const std::vector<CModelMeshData>& GetMeshes()const
	{
		return mMeshes;
	}
};
