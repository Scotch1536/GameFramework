//!
//! @file
//! @brief ���f���f�[�^�̃w�b�_�[�t�@�C��
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

//! @brief ���f���f�[�^�N���X
class CModelData
{
private:
	AssimpScene mAssimpScene;					//!< Assimp�V�[��
	std::string mDirectory;						//!< �e�N�X�`���t�@�C���̃p�X

	std::vector<CModelMeshData> mMeshes;		//!< ���b�V��
	std::vector<STexture> mTexturesLoaded;		//!< ���Ƀ��[�h����Ă���e�N�X�`��
	std::vector<SMaterial> mMaterials;			//!< �}�e���A��

	//!
	//! @brief �m�[�h���
	//! @param[in] node ��͂���m�[�h
	//! @param[in] scene �V�[��
	//!
	void ProcessNode(aiNode* node , const aiScene* scene);

	//!
	//! @brief ���b�V�����
	//! @param[in] mesh ��͂��郁�b�V��
	//! @param[in] scene �V�[��
	//!
	CModelMeshData ProcessMesh(aiMesh* mesh , const aiScene* scene);

	//! @brief �}�e���A���̃��[�h
	void LoadMaterial();

	//!
	//! @brief �e�N�X�`���̃��[�h
	//! @param[in] mtrl �}�e���A��
	//! @param[in] type �e�N�X�`���^�C�v
	//! @param[in] typeName �e�N�X�`����
	//! @param[in] scene �V�[��
	//! @return std::vector<STexture> ���ʂ̃e�N�X�`��
	//!
	std::vector<STexture> LoadTextures(aiMaterial* mtrl ,aiTextureType type ,std::string typeName ,const aiScene* scene);

	//!
	//! @brief �e�N�X�`��������
	//! @param[in] target �������������e�N�X�`��
	//!
	void TextureInit(STexture& target);

	//! @brief �ǂݍ��݃f�[�^������
	void ReadDataInit();

public:
	//! @brief �R���X�g���N�^
	CModelData() = default;

	//! @brief �f�X�g���N�^
	~CModelData();

	//!
	//! @brief ���f���f�[�^�̃��[�h
	//! @param[in] resourceFolderPath ���\�[�X�t�H���_�̃p�X
	//! @param[in] filePath ���f���t�@�C���̃p�X
	//! @return bool ���[�h������������
	//!
	bool Load(std::string resourceFolderPath , std::string filePath);

	//!
	//! @brief �L���b�V���f�[�^�̏�������
	//! @param[in] partner ���f���f�[�^�}�l�[�W���[�̎Q��
	//! @param[in] file �������ރt�@�C��
	//!
	void WriteCacheData(const CModelDataManager& partner , std::fstream& file);

	//!
	//! @brief �L���b�V���f�[�^�̓ǂݍ���
	//! @param[in] partner ���f���f�[�^�}�l�[�W���[�̎Q��
	//! @param[in] file �ǂݍ��ރt�@�C��
	//!
	void ReadCacheData(const CModelDataManager& partner , std::fstream& file);

	const std::vector<CModelMeshData>& GetMeshes()const
	{
		return mMeshes;
	}
};
