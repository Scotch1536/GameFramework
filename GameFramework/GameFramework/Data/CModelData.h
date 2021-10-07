#pragma once
#include <d3d11.h>
#include <DirectXMath.h>
#include <vector>

#include "../ExternalLibrary/Assimp/assimp/include/assimp/scene.h"
#include "../ExternalLibrary/Assimp/assimp/include/assimp/Importer.hpp"
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/AssimpScene.h"

#include "VertexProto.h"
#include "CModelMeshData.h"

class CModelDataManager;

class CModelData
{
private:
	AssimpScene mAssimpScene;		// assimp scene
	std::string mDirectory;			// �e�N�X�`���t�@�C���̈ʒu

	std::vector<CModelMeshData> mMeshes;				// ���b�V���̏W�������f��
	std::vector<STexture> mTexturesLoaded;		// ���Ƀ��[�h����Ă���e�N�X�`��
	std::vector<SMaterial> mMaterials;			// �}�e���A���Q

	// �m�[�h�����
	void ProcessNode(aiNode* node , const aiScene* scene);

	// ���b�V�������
	CModelMeshData ProcessMesh(aiMesh* mesh , const aiScene* scene , int meshidx);

	// �}�e���A����ǂݍ���
	void LoadMaterial();

	// �}�e���A���ɑΉ������e�N�X�`�����擾����
	std::vector<STexture> LoadMaterialTextures(
		aiMaterial * mat ,
		aiTextureType type ,
		std::string typeName ,
		const aiScene * scene);

	void TextureInit(STexture& target);
	void ReadDataInit();

public:
	CModelData() = default;
	~CModelData();

	bool Load(std::string resourcefolder , std::string filename);

	void WriteData(const CModelDataManager& partner , std::fstream& file);
	void ReadData(const CModelDataManager& partner , std::fstream& file);

	const std::vector<CModelMeshData>& GetMeshes()const
	{
		return mMeshes;
	}
};
