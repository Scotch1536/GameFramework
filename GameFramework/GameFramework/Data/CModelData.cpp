#include <vector>
#include <fstream>

#include "../ExternalLibrary/Assimp/assimp/include/assimp/Importer.hpp"
#include "../ExternalLibrary/Assimp/assimp/include/assimp/scene.h"
#include "../ExternalLibrary/Assimp/assimp/include/assimp/postprocess.h"
#include "../ExternalLibrary/Assimp/assimp/include/assimp/cimport.h"
#include "../ExternalCode/Shader.h"
#include "../ExternalCode/Memory.h"
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/utftosjisconv.h"
#include "../Managers/CDirectXResourceManager.h"

#include "CModelData.h"
#include "VertexProto.h"

std::vector<STexture> CModelData::LoadMaterialTextures(
	aiMaterial* mtrl ,
	aiTextureType type ,
	std::string typeName ,
	const aiScene * scene)
{
	std::vector<STexture> textures;		// ���̃}�e���A���Ɋ֘A�Â���DIFFUSE�e�N�X�`���̃��X�g
	ID3D11Device* dev;
	ID3D11DeviceContext* devcon;

	dev = CDirectXGraphics::GetInstance()->GetDXDevice();
	devcon = CDirectXGraphics::GetInstance()->GetImmediateContext();

	// �}�e���A������e�N�X�`�������擾��(��{��1��)���[�v����
	for(unsigned int i = 0; i < mtrl->GetTextureCount(type); i++)
	{
		aiString str;

		// �}�e���A�����炉�Ԗڂ̃e�N�X�`���t�@�C�������擾����
		mtrl->GetTexture(type , i , &str);

		// �������Ƀ��[�h���ꂽ�e�N�X�`���ł���΃��[�h���X�L�b�v����
		bool skip = false;

		// ���[�h�ς݃e�N�X�`���������[�v����
		for(unsigned int j = 0; j < mTexturesLoaded.size(); j++)
		{
			// �t�@�C�����������ł�������ǂݍ��܂Ȃ�
			if(std::strcmp(mTexturesLoaded[j].Path.c_str() , str.C_Str()) == 0)
			{
				// �ǂݍ��ݍς݂̃e�N�X�`������DIFFUSE�e�N�X�`���̃��X�g�ɃZ�b�g
				textures.push_back(mTexturesLoaded[j]);
				skip = true;
				break;
			}
		}
		if(!skip)
		{   // �܂��ǂݍ��܂�Ă��Ȃ������ꍇ
			STexture tex;

			std::string filename = std::string(str.C_Str());
			std::string filenameonly = ExtractFileName(filename , '\\');		// �t�@�C�������擾
			filename = mDirectory + filenameonly;								// ���\�[�X�f�B���N�g���{�t�@�C����

			tex.Texture = CDirectXResourceManager::GetInstance().GetTextureSRV(filename);

			//bool sts = CreateSRVfromFile(
			//	filename.c_str() ,
			//	dev , devcon , &tex.texres , &tex.texture);
			//if(!sts)
			//{
			//	// �������������t�s�e�W�Őݒ肳��Ă����ꍇ�ɑΉ�
			//	filenameonly = utf8_to_multi_winapi(std::string(filenameonly.c_str()));
			//	filename = m_directory + filenameonly;	// ���\�[�X�f�B���N�g���{�t�@�C����

			//	bool sts = CreateSRVfromFile(
			//		filename.c_str() ,
			//		dev , devcon , &tex.texres , &tex.texture);
			//	if(!sts)
			//	{
			//		MessageBox(nullptr , "Texture couldn't be loaded" , "Error!" , MB_ICONERROR | MB_OK);
			//		tex.texture = nullptr;
			//	}
			//}

			tex.Type = typeName;
			tex.Path = str.C_Str();
			// �e�N�X�`������DIFFUSE�e�N�X�`���̃��X�g�ɃZ�b�g
			textures.push_back(tex);
			this->mTexturesLoaded.push_back(tex);	// ���̃��f���Ɋ֘A�Â����e�N�X�`�����X�g�ɃZ�b�g
		}
	}

	return textures;
}

CModelData::~CModelData()
{
	// assimp scene ���
	mAssimpScene.Exit();
}

void CModelData::LoadMaterial()
{
	// �}�e���A�������݂��邩�H
	if(mAssimpScene.GetScene()->HasMaterials())
	{
		// �}�e���A���� �擾
		int nummaterial = mAssimpScene.GetScene()->mNumMaterials;

		for(int i = 0; i < nummaterial; i++)
		{
			SMaterial mtrl;

			// i�Ԗڂ̃}�e���A�����擾
			aiMaterial* mat = mAssimpScene.GetScene()->mMaterials[i];

			aiColor3D colordiffuse(1.f , 1.f , 1.f);
			mat->Get(AI_MATKEY_COLOR_DIFFUSE , colordiffuse);
			mtrl.Diffuse.x = colordiffuse.r;
			mtrl.Diffuse.y = colordiffuse.g;
			mtrl.Diffuse.z = colordiffuse.b;
			mtrl.Diffuse.x = 1.0f;
			mtrl.Diffuse.y = 1.0f;
			mtrl.Diffuse.z = 1.0f;

			aiColor3D colorspecular(0.f , 0.f , 0.f);
			mat->Get(AI_MATKEY_COLOR_SPECULAR , colorspecular);
			mtrl.Specular.x = colorspecular.r;
			mtrl.Specular.y = colorspecular.g;
			mtrl.Specular.z = colorspecular.b;

			aiColor3D colorambient(0.f , 0.f , 0.f);
			mat->Get(AI_MATKEY_COLOR_AMBIENT , colorambient);
			mtrl.Ambient.x = colorambient.r;
			mtrl.Ambient.y = colorambient.g;
			mtrl.Ambient.z = colorambient.b;

			aiColor3D coloremissive(0.f , 0.f , 0.f);
			mat->Get(AI_MATKEY_COLOR_EMISSIVE , coloremissive);
			mtrl.Emissive.x = coloremissive.r;
			mtrl.Emissive.y = coloremissive.g;
			mtrl.Emissive.z = coloremissive.b;

			float power;
			mat->Get(AI_MATKEY_SHININESS_STRENGTH , power);
			mtrl.SpecularPower = power;

			mMaterials.push_back(mtrl);
		}
	}
}

bool CModelData::Load(std::string resourceFolderPath ,
	std::string filePath)
{
	bool sts = mAssimpScene.Init(filePath);
	if(!sts)
	{
		MessageBox(nullptr , "ModelData load error" , "error" , MB_OK);
		return false;
	}

	mDirectory = resourceFolderPath;		// ���̃��f���̃e�N�X�`�������݂���f�B���N�g��

	LoadMaterial();						// ���̃��f���Ŏg�p����Ă���}�e���A�����擾����

	// ai�m�[�h����͂���
	ProcessNode(mAssimpScene.GetScene()->mRootNode , mAssimpScene.GetScene());

	return true;
}

// ���b�V���̉��
CModelMeshData CModelData::ProcessMesh(aiMesh * mesh , const aiScene * scene , int meshidx)
{
	std::vector<SVertexUV> vertices;			// ���_
	std::vector<unsigned int> indices;		// �ʂ̍\�����
	std::vector<STexture> textures;			// �e�N�X�`��
	SMaterial mtrl;

	// ���_�����擾
	for(unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		SVertexUV vertex;

		vertex.Pos.x = mesh->mVertices[i].x;
		vertex.Pos.y = mesh->mVertices[i].y;
		vertex.Pos.z = mesh->mVertices[i].z;

		// �@���x�N�g�������݂��邩�H
		if(mesh->HasNormals())
		{
			vertex.Normal.x = mesh->mNormals[i].x;
			vertex.Normal.y = mesh->mNormals[i].y;
			vertex.Normal.z = mesh->mNormals[i].z;
		}
		else
		{
			vertex.Normal.x = 0.0f;
			vertex.Normal.y = 0.0f;
			vertex.Normal.z = 0.0f;
		}

		// �e�N�X�`�����W�i�O�Ԗځj�����݂��邩�H
		if(mesh->HasTextureCoords(0))
		{
			vertex.Tex.x = mesh->mTextureCoords[0][i].x;
			vertex.Tex.y = mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}

	// �e�N�X�`�������擾����
	if(mesh->mMaterialIndex >= 0)
	{
		// ���̃��b�V���̃}�e���A���C���f�b�N�X�l���擾����
		int	mtrlidx = mesh->mMaterialIndex;

		// ���̃��b�V���̃}�e���A�����擾����
		mtrl = mMaterials[mtrlidx];

		// �V�[������}�e���A���f�[�^���擾����
		aiMaterial* material = scene->mMaterials[mtrlidx];

		// ���̃}�e���A���Ɋ֘A�Â����e�N�X�`�������o��
		std::vector<STexture> diffuseMaps = LoadMaterialTextures(material , aiTextureType_DIFFUSE , "texture_diffuse" , scene);

		// ���̃��b�V���Ŏg�p���Ă���e�N�X�`����ۑ�
		textures.insert(textures.end() , diffuseMaps.begin() , diffuseMaps.end());
	}

	// �ʂ̍\�������擾
	for(unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];

		for(unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	return CModelMeshData(vertices , indices , textures , mtrl);
}

// �m�[�h�̉��
void CModelData::ProcessNode(aiNode * node , const aiScene * scene)
{
	// �m�[�h���̃��b�V���̐������[�v����
	for(unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		int meshindex = node->mMeshes[i];			// �m�[�h��i�Ԗڃ��b�V���̃C���f�b�N�X���擾
		aiMesh* mesh = scene->mMeshes[meshindex];	// �V�[�����烁�b�V���{�̂����o��

		mMeshes.push_back(this->ProcessMesh(mesh , scene , meshindex));
	}

	// �q�m�[�h�ɂ��Ă����
	for(unsigned int i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i] , scene);
	}
}

void CModelData::WriteData(const CModelDataManager& partner , std::fstream& file)
{
	size_t bufSize;

	//AssimpScene�͕K�v�Ȃ��̂ŃV�[�N
	file.seekp(sizeof(AssimpScene) , std::ios_base::cur);

	//string�͂�����x�̕�����𒴂���Ɠǂݎ�肪���s����̂ŕ�����̑傫�����v�Z������ŏo��
	bufSize = mDirectory.size() * sizeof(char);
	file.write((char*)&bufSize , sizeof(size_t));
	file.write((char*)mDirectory.c_str() , bufSize);

	//vector��resize���K�v�Ȉ׃T�C�Y�����O�ɏo��
	bufSize = mMeshes.size();
	file.write((char*)&bufSize , sizeof(size_t));

	//Mesh���ɂ�vector�����݂���̂őS�Ĉ���o��
	for(auto& mesh : mMeshes)
	{
		file.seekp(sizeof(ComPtr<ID3D11Buffer>) * 3 , std::ios_base::cur);

		bufSize = mesh.Vertices.size();
		file.write((char*)&bufSize , sizeof(size_t));
		bufSize *= sizeof(mesh.Vertices[0]);
		file.write((char*)&bufSize , sizeof(size_t));
		file.write((char*)&mesh.Vertices[0] , bufSize);

		bufSize = mesh.Indices.size();
		file.write((char*)&bufSize , sizeof(size_t));
		bufSize *= sizeof(mesh.Indices[0]);
		file.write((char*)&bufSize , sizeof(size_t));
		file.write((char*)&mesh.Indices[0] , bufSize);

		bufSize = mesh.Textures.size();
		file.write((char*)&bufSize , sizeof(size_t));

		for(auto& texture : mesh.Textures)
		{
			bufSize = texture.Type.size() * sizeof(char);
			file.write((char*)&bufSize , sizeof(size_t));
			file.write((char*)texture.Type.c_str() , bufSize);

			bufSize = texture.Path.size() * sizeof(char);
			file.write((char*)&bufSize , sizeof(size_t));
			file.write((char*)texture.Path.c_str() , bufSize);

			file.seekp(sizeof(ID3D11ShaderResourceView*) , std::ios_base::cur);
		}

		file.write((char*)&mesh.Material , sizeof(SMaterial));
	}

	bufSize = mTexturesLoaded.size();
	file.write((char*)&bufSize , sizeof(size_t));

	//Texture�ɂ�string������̂ň���o��
	for(auto& texture : mTexturesLoaded)
	{
		bufSize = texture.Type.size() * sizeof(char);
		file.write((char*)&bufSize , sizeof(size_t));
		file.write((char*)texture.Type.c_str() , bufSize);

		bufSize = texture.Path.size() * sizeof(char);
		file.write((char*)&bufSize , sizeof(size_t));
		file.write((char*)texture.Path.c_str() , bufSize);

		file.seekp(sizeof(ID3D11ShaderResourceView*) , std::ios_base::cur);
	}

	bufSize = mMaterials.size();
	file.write((char*)&bufSize , sizeof(size_t));
	bufSize *= sizeof(mMaterials[0]);
	file.write((char*)&bufSize , sizeof(size_t));
	file.write((char*)&mMaterials[0] , bufSize);
}

void CModelData::ReadData(const CModelDataManager& partner , std::fstream& file)
{
	size_t bufSize;

	file.seekg(sizeof(AssimpScene) , std::ios_base::cur);

	file.read((char*)&bufSize , sizeof(size_t));
	mDirectory.resize(bufSize);
	file.read((char*)&mDirectory[0] , bufSize);

	file.read((char*)&bufSize , sizeof(size_t));

	mMeshes.resize(bufSize);

	for(auto& mesh : mMeshes)
	{
		file.seekg(sizeof(ComPtr<ID3D11Buffer>) * 3 , std::ios_base::cur);

		file.read((char*)&bufSize , sizeof(size_t));
		mesh.Vertices.resize(bufSize);
		file.read((char*)&bufSize , sizeof(size_t));
		file.read((char*)&mesh.Vertices[0] , bufSize);

		file.read((char*)&bufSize , sizeof(size_t));
		mesh.Indices.resize(bufSize);
		file.read((char*)&bufSize , sizeof(size_t));
		file.read((char*)&mesh.Indices[0] , bufSize);

		file.read((char*)&bufSize , sizeof(size_t));
		mesh.Textures.resize(bufSize);

		for(auto& texture : mesh.Textures)
		{
			file.read((char*)&bufSize , sizeof(size_t));
			texture.Type.resize(bufSize);
			file.read((char*)&texture.Type[0] , bufSize);

			file.read((char*)&bufSize , sizeof(size_t));
			texture.Path.resize(bufSize);
			file.read((char*)&texture.Path[0] , bufSize);

			file.seekg(sizeof(ID3D11ShaderResourceView*) , std::ios_base::cur);
		}

		file.read((char*)&mesh.Material , sizeof(SMaterial));
	}

	file.read((char*)&bufSize , sizeof(size_t));
	mTexturesLoaded.resize(bufSize);

	for(auto& texture : mTexturesLoaded)
	{
		file.read((char*)&bufSize , sizeof(size_t));
		texture.Type.resize(bufSize);
		file.read((char*)&texture.Type[0] , bufSize);

		file.read((char*)&bufSize , sizeof(size_t));
		texture.Path.resize(bufSize);
		file.read((char*)&texture.Path[0] , bufSize);

		file.seekg(sizeof(ID3D11ShaderResourceView*) , std::ios_base::cur);
	}

	file.read((char*)&bufSize , sizeof(size_t));
	mMaterials.resize(bufSize);
	file.read((char*)&bufSize , sizeof(size_t));
	file.read((char*)&mMaterials[0] , bufSize);
}

void CModelData::ReadDataInit(const CModelDataManager& partner)
{
	for(auto& mesh : mMeshes)
	{
		mesh.SetupMesh();

		for(auto& texture : mesh.Textures)
		{
			TextureInit(texture);
		}
	}

	for(auto& texture : mTexturesLoaded)
	{
		TextureInit(texture);
	}
}

void CModelData::TextureInit(STexture& target)
{
	std::string filename = target.Path;
	std::string filenameonly = ExtractFileName(filename , '\\');		// �t�@�C�������擾
	filename = mDirectory + filenameonly;								// ���\�[�X�f�B���N�g���{�t�@�C����

	target.Texture = CDirectXResourceManager::GetInstance().GetTextureSRV(filename);
}
