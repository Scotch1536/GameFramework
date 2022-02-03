//!
//! @file
//! @brief DirectXリソースマネージャーのソースファイル
//!

#include <filesystem>
#include "../ExternalCode/Shader.h"

#include "CDirectXResourceManager.h"

CDirectXResourceManager::CDirectXResourceManager()
{
	//指定のパスにファイルがない場合
	if(!std::filesystem::exists("Assets/Textures/White/white.bmp"))
	{
		//ディレクトリを作成
		std::filesystem::create_directories("Assets/Textures/White");

		//指定のパスにファイルがない場合
		if(std::filesystem::exists("GameFramework/Assets/white.bmp"))
		{
			//ファイルをコピーする
			std::filesystem::copy("GameFramework/Assets/white.bmp" , "Assets/Textures/White/white.bmp");
		}
		else
		{
			MessageBox(nullptr , 
				"white.bmpが見つかりません\nGameFrameworkのフォルダを実行ファイルのカレントディレクトリに配置して実行してください\nその後white.bmpが\"Assets/Textures/White/\"に作成されます" ,
				"Error" , MB_OK);

			//実行を強制終了する
			exit(1);
		}
	}

	GetTextureSRV("Assets/Textures/White/white.bmp");
}

CDirectXResourceManager& CDirectXResourceManager::GetInstance()
{
	static CDirectXResourceManager instance;

	return instance;
}

ID3D11ShaderResourceView* CDirectXResourceManager::GetTextureSRV(std::string filePath)
{
	//存在しなければ
	if(mTextureSRV.count(filePath) == 0)
	{
		mTextureResource[filePath];
		mTextureSRV[filePath];

		CDirectXGraphics& buf = *CDirectXGraphics::GetInstance();

		//SRVを作成
		bool sts = CreateSRVfromFile(
			filePath.c_str() , buf.GetDXDevice() , buf.GetImmediateContext() ,
			mTextureResource[filePath].GetAddressOf() , mTextureSRV[filePath].GetAddressOf());
		if(!sts)
		{
			MessageBox(nullptr , "Texture couldn't be loaded" , "Error!" , MB_ICONERROR | MB_OK);
			mTextureResource[filePath] = nullptr;
			mTextureSRV[filePath] = nullptr;
			exit(1);
		}
	}
	return mTextureSRV[filePath].Get();
}

ID3D11VertexShader* CDirectXResourceManager::GetVertexShader(std::string filePath)
{
	//存在しなければ
	if(mVertexShader.count(filePath) == 0)
	{
		mVertexShader[filePath];

		ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();

		//頂点シェーダーを作成
		bool sts = CreateVertexShader(
			device ,
			filePath.c_str() ,
			"main" ,
			"vs_5_0" ,
			nullptr ,
			0 ,
			&mVertexShader[filePath] ,
			nullptr);
		if(!sts)
		{
			MessageBox(nullptr , "CreateVertexShader Error" , "Error" , MB_OK);
		}
	}
	return mVertexShader[filePath].Get();
}

ID3D11PixelShader* CDirectXResourceManager::GetPixelShader(std::string filePath)
{
	//存在しなければ
	if(mPixelShader.count(filePath) == 0)
	{
		mPixelShader[filePath];

		ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();

		//ピクセルシェーダーを作成
		bool sts = CreatePixelShader(
			device ,
			filePath.c_str() ,
			"main" ,
			"ps_5_0" ,
			&mPixelShader[filePath]);
		if(!sts)
		{
			MessageBox(nullptr , "CreatePixelShader Error" , "Error" , MB_OK);
		}
	}
	return mPixelShader[filePath].Get();
}

void CDirectXResourceManager::CreateVertexLayout(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , std::string vsFilePath)
{
	//存在しなければ
	if(mVertexLayout.count(vsFilePath) == 0)
	{
		mVertexLayout[vsFilePath];

		ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();

		//頂点シェーダーを生成
		bool sts = CreateVertexShader(
			device ,
			vsFilePath.c_str() ,
			"main" ,
			"vs_5_0" ,
			layout ,
			layoutSize ,
			nullptr ,
			&mVertexLayout[vsFilePath]);
		if(!sts)
		{
			MessageBox(nullptr , "CreateVertexShader Error" , "Error" , MB_OK);
		}
	}
}

ID3D11InputLayout* CDirectXResourceManager::GetVertexLayout(std::string vsFilePath)
{
	//存在しなければ
	if(mVertexLayout.count(vsFilePath) == 0)
	{
		MessageBox(nullptr , "頂点レイアウトが見つかりませんでした" , "Error" , MB_OK);
		return nullptr;
	}
	return mVertexLayout[vsFilePath].Get();
}

ID3D11InputLayout* CDirectXResourceManager::GetVertexLayout(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , std::string vsFilePath)
{
	//存在しなければ
	if(mVertexLayout.count(vsFilePath) == 0)
	{
		CreateVertexLayout(layout , layoutSize , vsFilePath);
	}
	return mVertexLayout[vsFilePath].Get();
}
