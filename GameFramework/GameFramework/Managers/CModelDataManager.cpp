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
	std::string beforeBuf;
	std::vector<std::string> fileDirectoryComponents;

	while(1)
	{
		beforeBuf = buf;
		std::getline(refString , buf , '/');

		if(buf == beforeBuf)
		{
			fileName = fileDirectoryComponents.back();
			break;
		}
		else
		{
			fileDirectoryComponents.emplace_back(beforeBuf);
		}
	}

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
			"�����[�X���[�h�ł̓��f���f�[�^�̓L���b�V���f�[�^�ł���������Ă��܂���B\n�f�o�b�O���[�h�ň�x�������đS�Ẵ��f���f�[�^�̃L���b�V���f�[�^���쐬���Ă��������B" ,
			"error" , MB_OK);
		exit(1);
#endif

		return false;
	}
	else
	{
		target.ReadCacheData(*this , file);
		file.close();

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
		target.WriteCacheData(*this , file);
		file.close();
	}
}

CModelData& CModelDataManager::GetModel(std::string filePath , std::string resourceFolderPath)
{
	if(mModelData.count(filePath) == 0)
	{
		mModelData[filePath];		//���f���f�[�^�쐬

		if(!InputFile(mModelData[filePath] , filePath))
		{
			//���f���f�[�^������
			if(!mModelData[filePath].Load(resourceFolderPath , filePath))
			{
				MessageBox(nullptr , "LoadModels function error" , "error" , MB_OK);
			}

			OutputFile(mModelData[filePath] , filePath);
		}
	}
	return mModelData[filePath];
}
