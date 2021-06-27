#pragma once
#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>

#include "../ExternalLibrary/Assimp/assimp/include/assimp/scene.h"
#include "../ExternalLibrary/Assimp/assimp/include/assimp/Importer.hpp"

#include "Mesh.h"
#include "CDirectxGraphics.h"
#include "AssimpScene.h"
#include "VertexProto.h"

class CModelDataManager;

class ModelData
{
public:
	ModelData() = default;
	~ModelData();

	bool Load(std::string resourcefolder , std::string filename);

	const std::vector<Mesh>& GetMeshes()const
	{
		return m_meshes;
	}

private:
	AssimpScene m_assimpscene;					// assimp scene
	std::vector<Mesh> m_meshes;					// ���b�V���̏W�������f��
	std::string m_directory;					// �e�N�X�`���t�@�C���̈ʒu
	std::vector<Texture> m_texturesloaded;		// ���Ƀ��[�h����Ă���e�N�X�`��
	std::vector<Material> m_materials;			// �}�e���A���Q

	void processNode(aiNode* node , const aiScene* scene);				// �m�[�h�����
	Mesh processMesh(aiMesh* mesh , const aiScene* scene , int meshidx);	// ���b�V�������

	void LoadMaterial();						// �}�e���A����ǂݍ���

	// �}�e���A���ɑΉ������e�N�X�`�����擾����
	std::vector<Texture> loadMaterialTextures(
		aiMaterial * mat ,
		aiTextureType type ,
		std::string typeName ,
		const aiScene * scene);

	void Exit();
};
