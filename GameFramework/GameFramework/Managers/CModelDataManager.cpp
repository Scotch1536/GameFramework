//!
//! @file
//! @brief モデルデータマネージャーのソースファイル
//!

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>

#include "../ExternalCode/AssimpScene.h"

#include "CModelDataManager.h"

std::string CModelDataManager::MakeFileName(std::string filePath)
{
	//キャッシュデータのディレクトリパスが存在しなければ
	if(!std::filesystem::exists(mModelDataCachePath))
	{
		//ディレクトリ作成
		std::filesystem::create_directory(mModelDataCachePath);
	}

	std::string fileName;
	std::stringstream refString { filePath };
	std::string buf;
	std::string beforeBuf;
	std::vector<std::string> fileDirectoryComponents;

	//ファイル名作成処理
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
		MessageBox(nullptr , "ファイルを開けませんでした(input)" , "Error" , MB_OK);

#ifndef _DEBUG
		MessageBox(nullptr ,
			"リリースモードではモデルデータはキャッシュデータでしか許されていません。\nデバッグモードで一度動かして全てのモデルデータのキャッシュデータを作成してください。" ,
			"Error" , MB_OK);

		//実行を強制終了
		exit(1);
#endif

		return false;
	}
	else
	{
		//キャッシュデータ読み込み
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
		MessageBox(nullptr , "ファイルを開けませんでした(output)" , "Error" , MB_OK);
	}
	else
	{
		//キャッシュデータ書き込み
		target.WriteCacheData(*this , file);

		file.close();
	}
}

CModelData& CModelDataManager::GetModel(std::string filePath , std::string resourceFolderPath)
{
	if(mModelData.count(filePath) == 0)
	{
		mModelData[filePath];		//モデルデータ作成

		//キャッシュデータの入力が失敗したら
		if(!InputCache(mModelData[filePath] , filePath))
		{
			//モデルデータ初期化
			if(!mModelData[filePath].Load(resourceFolderPath , filePath))
			{
				MessageBox(nullptr , "モデルデータの初期化に失敗しました" , "Error" , MB_OK);
			}

			//キャッシュデータ出力
			OutputCache(mModelData[filePath] , filePath);
		}
	}
	return mModelData[filePath];
}
