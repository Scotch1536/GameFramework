#include "../ExternalCode/Shader.h"

#include "CDirectXResourceManager.h"

CDirectXResourceManager& CDirectXResourceManager::GetInstance()
{
	static CDirectXResourceManager instance;

	return instance;
}

ID3D11ShaderResourceView* CDirectXResourceManager::GetTextureSRV(std::string filePath)
{
	if(mTextureSRVMap.count(filePath) == 0)
	{
		mTextureResourceMap[filePath];
		mTextureSRVMap[filePath];

		CDirectXGraphics& buf = *CDirectXGraphics::GetInstance();

		bool sts = CreateSRVfromFile(
			filePath.c_str() , buf.GetDXDevice() , buf.GetImmediateContext() ,
			mTextureResourceMap[filePath].GetAddressOf() , mTextureSRVMap[filePath].GetAddressOf());
		if(!sts)
		{
			MessageBox(nullptr , "Texture couldn't be loaded" , "Error!" , MB_ICONERROR | MB_OK);
			mTextureResourceMap[filePath] = nullptr;
			mTextureSRVMap[filePath] = nullptr;
			exit(1);
		}
	}
	return mTextureSRVMap[filePath].Get();
}

ID3D11VertexShader* CDirectXResourceManager::GetVertexShader(std::string filePath)
{
	if(mVertexShaderMap.count(filePath) == 0)
	{
		mVertexShaderMap[filePath];

		ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();

		// 頂点シェーダーを生成
		bool sts = CreateVertexShader(
			device ,
			filePath.c_str() ,
			"main" ,
			"vs_5_0" ,
			nullptr ,
			0 ,
			&mVertexShaderMap[filePath] ,
			nullptr);
		if(!sts)
		{
			MessageBox(nullptr , "CreateVertexShader error" , "error" , MB_OK);
		}
	}
	return mVertexShaderMap[filePath].Get();
}

ID3D11PixelShader* CDirectXResourceManager::GetPixelShader(std::string filePath)
{
	if(mPixelShaderMap.count(filePath) == 0)
	{
		mPixelShaderMap[filePath];

		ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();

		// ピクセルシェーダーを生成
		bool sts = CreatePixelShader(
			device ,
			filePath.c_str() ,
			"main" ,
			"ps_5_0" ,
			&mPixelShaderMap[filePath]);
		if(!sts)
		{
			MessageBox(nullptr , "CreatePixelShader error" , "error" , MB_OK);
		}
	}
	return mPixelShaderMap[filePath].Get();
}

ID3D11InputLayout* CDirectXResourceManager::GetVertexLayout(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , std::string vsFilePath)
{
	if(mVertexLayoutMap.count(vsFilePath) == 0)
	{
		mVertexLayoutMap[vsFilePath];

		ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();

		// 頂点シェーダーを生成
		bool sts = CreateVertexShader(
			device ,
			vsFilePath.c_str() ,
			"main" ,
			"vs_5_0" ,
			layout ,
			layoutSize ,
			nullptr ,
			&mVertexLayoutMap[vsFilePath]);
		if(!sts)
		{
			MessageBox(nullptr , "CreateVertexShader error" , "error" , MB_OK);
		}
	}
	return mVertexLayoutMap[vsFilePath].Get();
}
