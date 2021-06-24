#pragma once
#include <memory>
#include <unordered_map>
#include <string>

#include "../ExternalCode/ModelData.h"

class CModelDataManager
{
private:
	CModelDataManager() = default;
	~CModelDataManager() = default;
public:
	CModelDataManager(const CModelDataManager&) = delete;
	CModelDataManager& operator=(const CModelDataManager&) = delete;
	CModelDataManager(CModelDataManager&&) = delete;
	CModelDataManager& operator=(CModelDataManager&&) = delete;

	static CModelDataManager& GetInstance()
	{
		static CModelDataManager instance;
		return instance;
	}

	//���f�����擾����
	const ModelData& GetModel(std::string filePath , std::string resourceFolderPath);
private:
	std::unordered_map<std::string , ModelData> mModelData;		//���f���f�[�^�i�[����
};
