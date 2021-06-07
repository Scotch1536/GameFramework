#include "CModelDataManager.h"

ModelData* CModelManager::GetModel(std::string filename , std::string resourcefolder)
{
	if (mModelData.count(filename) == 0) {
		mModelData[filename];		//モデルデータ作成

		//モデルデータ初期化
		if (!mModelData[filename].Load(resourcefolder,filename))
		{
			MessageBox(nullptr, "LoadModels function error", "error", MB_OK);
		}
	}
	return &mModelData[filename];
}
