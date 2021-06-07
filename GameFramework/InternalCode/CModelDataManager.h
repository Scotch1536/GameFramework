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

	//���f���i�̃|�C���^�j���擾����
	ModelData* GetModel(std::string filename , std::string resourcefolder);
private:
	std::unordered_map<std::string , ModelData> mModelData;		//���f���f�[�^�i�[����
};
