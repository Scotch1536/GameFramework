#pragma once

#include "ModelData.h"
#include <unordered_map>
#include <string>

class CModelManager
{
private:
	CModelManager() = default;
	~CModelManager() = default;
public:
	CModelManager(const CModelManager&) = delete;
	CModelManager& operator=(const CModelManager&) = delete;
	CModelManager(CModelManager&&) = delete;
	CModelManager& operator=(CModelManager&&) = delete;

	static CModelManager& GetInstance()
	{
		static CModelManager instance;
		return instance;
	}

	ModelData& GetModel(std::string filename , std::string resourcefolder);		//モデル（のポインタ）を取得する
private:
	std::unordered_map<std::string , ModelData> mModelData;			//モデルデータ格納辞書
};
