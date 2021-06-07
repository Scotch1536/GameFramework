#pragma once

#include "ModelData.h"
#include <memory>
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

	//モデル（のポインタ）を取得する
	ModelData* GetModel(std::string filename , std::string resourcefolder);
private:
	std::unordered_map<std::string , ModelData> mModelData;		//モデルデータ格納辞書
};
