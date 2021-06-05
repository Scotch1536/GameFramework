#include "CModelDataManager.h"

ModelData& CModelManager::GetModel(std::string resourcefolder , std::string filename)
{
	if (mModelData.count(filename) == 0) {
		mModelData[filename];		//���f���f�[�^�쐬

		//���f���f�[�^������
		if (!mModelData[filename].Load(resourcefolder,filename))
		{
			MessageBox(nullptr, "LoadModels function error", "error", MB_OK);
		}
	}
	return mModelData[filename];
}
