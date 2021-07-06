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
	std::vector<STexture> textures;		// このマテリアルに関連づいたDIFFUSEテクスチャのリスト
	ID3D11Device* dev;
	ID3D11DeviceContext* devcon;

	dev = CDirectXGraphics::GetInstance()->GetDXDevice();
	devcon = CDirectXGraphics::GetInstance()->GetImmediateContext();

	// マテリアルからテクスチャ個数を取得し(基本は1個)ループする
	for(unsigned int i = 0; i < mtrl->GetTextureCount(type); i++)
	{
		aiString str;

		// マテリアルからｉ番目のテクスチャファイル名を取得する
		mtrl->GetTexture(type , i , &str);

		// もし既にロードされたテクスチャであればロードをスキップする
		bool skip = false;

		// ロード済みテクスチャ数分ループする
		for(unsigned int j = 0; j < mTexturesLoaded.size(); j++)
		{
			// ファイル名が同じであったら読み込まない
			if(std::strcmp(mTexturesLoaded[j].Path.c_str() , str.C_Str()) == 0)
			{
				// 読み込み済みのテクスチャ情報をDIFFUSEテクスチャのリストにセット
				textures.push_back(mTexturesLoaded[j]);
				skip = true;
				break;
			}
		}
		if(!skip)
		{   // まだ読み込まれていなかった場合
			STexture tex;

			std::string filename = std::string(str.C_Str());
			std::string filenameonly = ExtractFileName(filename , '\\');		// ファイル名を取得
			filename = mDirectory + filenameonly;								// リソースディレクトリ＋ファイル名

			tex.Texture = CDirectXResourceManager::GetInstance().GetTextureSRV(filename);

			//bool sts = CreateSRVfromFile(
			//	filename.c_str() ,
			//	dev , devcon , &tex.texres , &tex.texture);
			//if(!sts)
			//{
			//	// ｆｉｌｅ名がＵＴＦ８で設定されていた場合に対応
			//	filenameonly = utf8_to_multi_winapi(std::string(filenameonly.c_str()));
			//	filename = m_directory + filenameonly;	// リソースディレクトリ＋ファイル名

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
			// テクスチャ情報をDIFFUSEテクスチャのリストにセット
			textures.push_back(tex);
			this->mTexturesLoaded.push_back(tex);	// このモデルに関連づいたテクスチャリストにセット
		}
	}

	return textures;
}

CModelData::~CModelData()
{
	// assimp scene 解放
	mAssimpScene.Exit();
}

void CModelData::LoadMaterial()
{
	// マテリアルが存在するか？
	if(mAssimpScene.GetScene()->HasMaterials())
	{
		// マテリアル数 取得
		int nummaterial = mAssimpScene.GetScene()->mNumMaterials;

		for(int i = 0; i < nummaterial; i++)
		{
			SMaterial mtrl;

			// i番目のマテリアルを取得
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

	mDirectory = resourceFolderPath;		// このモデルのテクスチャが存在するディレクトリ

	LoadMaterial();						// このモデルで使用されているマテリアルを取得する

	// aiノードを解析する
	ProcessNode(mAssimpScene.GetScene()->mRootNode , mAssimpScene.GetScene());

	return true;
}

// メッシュの解析
CModelMeshData CModelData::ProcessMesh(aiMesh * mesh , const aiScene * scene , int meshidx)
{
	std::vector<SVertexUV> vertices;			// 頂点
	std::vector<unsigned int> indices;		// 面の構成情報
	std::vector<STexture> textures;			// テクスチャ
	SMaterial mtrl;

	// 頂点情報を取得
	for(unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		SVertexUV vertex;

		vertex.Pos.x = mesh->mVertices[i].x;
		vertex.Pos.y = mesh->mVertices[i].y;
		vertex.Pos.z = mesh->mVertices[i].z;

		// 法線ベクトルが存在するか？
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

		// テクスチャ座標（０番目）が存在するか？
		if(mesh->HasTextureCoords(0))
		{
			vertex.Tex.x = mesh->mTextureCoords[0][i].x;
			vertex.Tex.y = mesh->mTextureCoords[0][i].y;
		}

		vertices.push_back(vertex);
	}

	// テクスチャ情報を取得する
	if(mesh->mMaterialIndex >= 0)
	{
		// このメッシュのマテリアルインデックス値を取得する
		int	mtrlidx = mesh->mMaterialIndex;

		// このメッシュのマテリアルを取得する
		mtrl = mMaterials[mtrlidx];

		// シーンからマテリアルデータを取得する
		aiMaterial* material = scene->mMaterials[mtrlidx];

		// このマテリアルに関連づいたテクスチャを取り出す
		std::vector<STexture> diffuseMaps = LoadMaterialTextures(material , aiTextureType_DIFFUSE , "texture_diffuse" , scene);

		// このメッシュで使用しているテクスチャを保存
		textures.insert(textures.end() , diffuseMaps.begin() , diffuseMaps.end());
	}

	// 面の構成情報を取得
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

// ノードの解析
void CModelData::ProcessNode(aiNode * node , const aiScene * scene)
{
	// ノード内のメッシュの数分ループする
	for(unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		int meshindex = node->mMeshes[i];			// ノードのi番目メッシュのインデックスを取得
		aiMesh* mesh = scene->mMeshes[meshindex];	// シーンからメッシュ本体を取り出す

		mMeshes.push_back(this->ProcessMesh(mesh , scene , meshindex));
	}

	// 子ノードについても解析
	for(unsigned int i = 0; i < node->mNumChildren; i++)
	{
		this->ProcessNode(node->mChildren[i] , scene);
	}
}

void CModelData::WriteData(const CModelDataManager& partner , std::fstream& file)
{
	size_t bufSize;

	//AssimpSceneは必要ないのでシーク
	file.seekp(sizeof(AssimpScene) , std::ios_base::cur);

	//stringはある程度の文字列を超えると読み取りが失敗するので文字列の大きさを計算した上で出力
	bufSize = mDirectory.size() * sizeof(char);
	file.write((char*)&bufSize , sizeof(size_t));
	file.write((char*)mDirectory.c_str() , bufSize);

	//vectorはresizeが必要な為サイズを事前に出力
	bufSize = mMeshes.size();
	file.write((char*)&bufSize , sizeof(size_t));

	//Mesh内にもvectorが存在するので全て一つずつ出力
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

	//Textureにはstringがあるので一つずつ出力
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
	std::string filenameonly = ExtractFileName(filename , '\\');		// ファイル名を取得
	filename = mDirectory + filenameonly;								// リソースディレクトリ＋ファイル名

	target.Texture = CDirectXResourceManager::GetInstance().GetTextureSRV(filename);
}
