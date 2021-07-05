#pragma once
#include <filesystem>
#include <memory>
#include <unordered_map>
#include <string>

#include "../ExternalCode/CModelData.h"

class CModelDataManager
{
private:
	std::unordered_map<std::string , CModelData> mModelData;		//���f���f�[�^�i�[����

	std::filesystem::path mModelDataCachePath = "./ModelDataCache";
	std::string mExtension = ".bin";

	CModelDataManager() = default;

	std::string MakeFileName(std::string filePath);
	bool InputFile(CModelData& target , std::string filePath);
	void OutputFile(CModelData& target , std::string filePath);
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
	CModelData& GetModel(std::string filePath , std::string resourceFolderPath);
};
