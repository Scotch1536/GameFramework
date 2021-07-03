#include "../ExternalCode/Shader.h"

#include "CDirectXResourceManager.h"

CDirectXResourceManager& CDirectXResourceManager::GetInstance()
{
	static CDirectXResourceManager instance;

	return instance;
}

ID3D11ShaderResourceView* CDirectXResourceManager::GetTextureSRV(std::string filePath)
{
	if(mTextureSRV.count(filePath) == 0)
	{
		mTextureResource[filePath];
		mTextureSRV[filePath];

		CDirectXGraphics& buf = *CDirectXGraphics::GetInstance();

		bool sts = CreateSRVfromFile(
			filePath.c_str() ,
			buf.GetDXDevice() , buf.GetImmediateContext() , mTextureResource[filePath].GetAddressOf() , mTextureSRV[filePath].GetAddressOf());
		if(!sts)
		{
			MessageBox(nullptr , "Texture couldn't be loaded" , "Error!" , MB_ICONERROR | MB_OK);
			mTextureSRV[filePath] = nullptr;
		}
	}
	return mTextureSRV[filePath].Get();
}