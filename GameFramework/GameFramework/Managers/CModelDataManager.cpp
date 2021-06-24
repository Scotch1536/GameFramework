#include "CModelDataManager.h"

const ModelData& CModelDataManager::GetModel(std::string filePath , std::string resourceFolderPath)
{
	if (mModelData.count(filePath) == 0) {
		mModelData[filePath];		//���f���f�[�^�쐬

		//���f���f�[�^������
		if (!mModelData[filePath].Load(resourceFolderPath,filePath))
		{
			MessageBox(nullptr, "LoadModels function error", "error", MB_OK);
		}
	}
	return mModelData[filePath];
}
