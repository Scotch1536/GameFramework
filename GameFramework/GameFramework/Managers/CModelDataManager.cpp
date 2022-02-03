//!
//! @file
//! @brief ���f���f�[�^�}�l�[�W���[�̃\�[�X�t�@�C��
//!

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../ExternalCode/AssimpScene.h"

#include "CModelDataManager.h"

std::string CModelDataManager::MakeFileName(std::string filePath)
{
	//�L���b�V���f�[�^�̃f�B���N�g���p�X�����݂��Ȃ����
	if(!std::filesystem::exists(mModelDataCachePath))
	{
		//�f�B���N�g���쐬
		std::filesystem::create_directory(mModelDataCachePath);
	}

	std::string fileName;
	std::stringstream refString { filePath };
	std::string buf;
	std::string beforeBuf;
	std::vector<std::string> fileDirectoryComponents;

	//�t�@�C�����쐬����
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

bool CModelDataManager::InputCache(CModelData& target , std::string filePath)
{
	std::fstream file;

	file.open(MakeFileName(filePath) , std::ios::binary | std::ios::in);
	if(!file)
	{
		MessageBox(nullptr , "�t�@�C�����J���܂���ł���(input)" , "Error" , MB_OK);

#ifndef _DEBUG
		MessageBox(nullptr ,
			"�����[�X���[�h�ł̓��f���f�[�^�̓L���b�V���f�[�^�ł���������Ă��܂���B\n�f�o�b�O���[�h�ň�x�������đS�Ẵ��f���f�[�^�̃L���b�V���f�[�^���쐬���Ă��������B" ,
			"Error" , MB_OK);

		//���s�������I��
		exit(1);
#endif

		return false;
	}
	else
	{
		//�L���b�V���f�[�^�ǂݍ���
		target.ReadCacheData(*this , file);

		file.close();

		return true;
	}
}

void CModelDataManager::OutputCache(CModelData& target , std::string filePath)
{
	std::fstream file;

	file.open(MakeFileName(filePath) , std::ios::binary | std::ios::out);

	if(!file)
	{
		MessageBox(nullptr , "�t�@�C�����J���܂���ł���(output)" , "Error" , MB_OK);
	}
	else
	{
		//�L���b�V���f�[�^��������
		target.WriteCacheData(*this , file);

		file.close();
	}
}

CModelData& CModelDataManager::GetModel(std::string filePath , std::string resourceFolderPath)
{
	if(mModelData.count(filePath) == 0)
	{
		mModelData[filePath];		//���f���f�[�^�쐬

		//�L���b�V���f�[�^�̓��͂����s������
		if(!InputCache(mModelData[filePath] , filePath))
		{
			//���f���f�[�^������
			if(!mModelData[filePath].Load(resourceFolderPath , filePath))
			{
				MessageBox(nullptr , "���f���f�[�^�̏������Ɏ��s���܂���" , "Error" , MB_OK);
			}

			//�L���b�V���f�[�^�o��
			OutputCache(mModelData[filePath] , filePath);
		}
	}
	return mModelData[filePath];
}
