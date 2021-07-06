#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../ExternalCode/AssimpScene.h"

#include "CModelDataManager.h"

std::string CModelDataManager::MakeFileName(std::string filePath)
{
	if(!std::filesystem::exists(mModelDataCachePath))
	{
		std::filesystem::create_directory(mModelDataCachePath);
	}

	std::string fileName;
	std::stringstream refString { filePath };
	std::string buf;
	std::getline(refString , buf , '/');
	std::getline(refString , buf , '/');
	if(buf == "Assets" || buf == "assets")
	{
		std::getline(refString , buf , '/');
	}

	fileName = buf;
	fileName += mExtension;

	return mModelDataCachePath.string() + "/" + fileName;
}

bool CModelDataManager::InputFile(CModelData& target , std::string filePath)
{
	std::fstream file;

	file.open(MakeFileName(filePath) , std::ios::binary | std::ios::in);
	if(!file)
	{
		MessageBox(nullptr , "Don't Open File(input)" , "error" , MB_OK);

#ifndef _DEBUG
		MessageBox(nullptr ,
			"リリースモードではモデルデータはキャッシュデータでしか許されていません。\nデバッグモードで一度動かして全てのモデルデータのキャッシュデータを作成してください。" ,
			"error" , MB_OK);
		exit(1);
#endif

		return false;
	}
	else
	{
		target.ReadData(*this , file);
		file.close();

		target.ReadDataInit(*this);

		return true;
	}
}

void CModelDataManager::OutputFile(CModelData& target , std::string filePath)
{
	std::fstream file;

	file.open(MakeFileName(filePath) , std::ios::binary | std::ios::out);

	if(!file)
	{
		MessageBox(nullptr , "Don't Open File(output)" , "error" , MB_OK);
	}
	else
	{
		target.WriteData(*this , file);
		file.close();
	}
}

CModelData& CModelDataManager::GetModel(std::string filePath , std::string resourceFolderPath)
{
	if(mModelData.count(filePath) == 0)
	{
		mModelData[filePath];		//モデルデータ作成

		if(!InputFile(mModelData[filePath] , filePath))
		{
			//モデルデータ初期化
			if(!mModelData[filePath].Load(resourceFolderPath , filePath))
			{
				MessageBox(nullptr , "LoadModels function error" , "error" , MB_OK);
			}

			OutputFile(mModelData[filePath] , filePath);
		}
	}
	return mModelData[filePath];
}
