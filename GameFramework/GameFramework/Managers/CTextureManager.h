#pragma once
#include <memory>
#include <unordered_map>
#include <string>

#include "../ExternalCode/CTextureData.h"

class CTextureManager
{
private:
	std::unordered_map<std::string, CTextureData> mTextureData;		//���f���f�[�^�i�[����

	CTextureManager() = default;
public:
	CTextureManager(const CTextureManager&) = delete;
	CTextureManager& operator=(const CTextureManager&) = delete;
	CTextureManager(CTextureManager&&) = delete;
	CTextureManager& operator=(CTextureManager&&) = delete;

	static CTextureManager& GetInstance()
	{
		static CTextureManager instance;
		return instance;
	}

	//���f�����擾����
	CTextureData& GetTexture(std::string filePath);
};
