#include	<wrl/client.h>
#include "CTextureManager.h"


CTextureData& CTextureManager::GetTexture(std::string filePath)
{
	if (mTextureData.count(filePath) == 0) {
		mTextureData[filePath];		//���f���f�[�^�쐬

		//���f���f�[�^������
		if (!mTextureData[filePath].Load(filePath))
		{
			MessageBox(nullptr, "LoadModels function error", "error", MB_OK);
		}
	}
	return mTextureData[filePath];
}
