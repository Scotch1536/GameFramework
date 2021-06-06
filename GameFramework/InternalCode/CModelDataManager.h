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

	ModelData& GetModel(std::string filename , std::string resourcefolder);		//���f���i�̃|�C���^�j���擾����
private:
	std::unordered_map<std::string , ModelData> mModelData;			//���f���f�[�^�i�[����
};
