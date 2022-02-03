//!
//! @file
//! @brief DirectX���\�[�X�}�l�[�W���[�̃\�[�X�t�@�C��
//!

#include <filesystem>
#include "../ExternalCode/Shader.h"

#include "CDirectXResourceManager.h"

CDirectXResourceManager::CDirectXResourceManager()
{
	//�w��̃p�X�Ƀt�@�C�����Ȃ��ꍇ
	if(!std::filesystem::exists("Assets/Textures/White/white.bmp"))
	{
		//�f�B���N�g�����쐬
		std::filesystem::create_directories("Assets/Textures/White");

		//�w��̃p�X�Ƀt�@�C�����Ȃ��ꍇ
		if(std::filesystem::exists("GameFramework/Assets/white.bmp"))
		{
			//�t�@�C�����R�s�[����
			std::filesystem::copy("GameFramework/Assets/white.bmp" , "Assets/Textures/White/white.bmp");
		}
		else
		{
			MessageBox(nullptr , 
				"white.bmp��������܂���\nGameFramework�̃t�H���_�����s�t�@�C���̃J�����g�f�B���N�g���ɔz�u���Ď��s���Ă�������\n���̌�white.bmp��\"Assets/Textures/White/\"�ɍ쐬����܂�" ,
				"Error" , MB_OK);

			//���s�������I������
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
	//���݂��Ȃ����
	if(mTextureSRV.count(filePath) == 0)
	{
		mTextureResource[filePath];
		mTextureSRV[filePath];

		CDirectXGraphics& buf = *CDirectXGraphics::GetInstance();

		//SRV���쐬
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
	//���݂��Ȃ����
	if(mVertexShader.count(filePath) == 0)
	{
		mVertexShader[filePath];

		ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();

		//���_�V�F�[�_�[���쐬
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
	//���݂��Ȃ����
	if(mPixelShader.count(filePath) == 0)
	{
		mPixelShader[filePath];

		ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();

		//�s�N�Z���V�F�[�_�[���쐬
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
	//���݂��Ȃ����
	if(mVertexLayout.count(vsFilePath) == 0)
	{
		mVertexLayout[vsFilePath];

		ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();

		//���_�V�F�[�_�[�𐶐�
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
	//���݂��Ȃ����
	if(mVertexLayout.count(vsFilePath) == 0)
	{
		MessageBox(nullptr , "���_���C�A�E�g��������܂���ł���" , "Error" , MB_OK);
		return nullptr;
	}
	return mVertexLayout[vsFilePath].Get();
}

ID3D11InputLayout* CDirectXResourceManager::GetVertexLayout(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , std::string vsFilePath)
{
	//���݂��Ȃ����
	if(mVertexLayout.count(vsFilePath) == 0)
	{
		CreateVertexLayout(layout , layoutSize , vsFilePath);
	}
	return mVertexLayout[vsFilePath].Get();
}
