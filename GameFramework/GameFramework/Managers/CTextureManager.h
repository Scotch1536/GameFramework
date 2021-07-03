#pragma once
#include <memory>
#include <unordered_map>
#include <string>

#include "../Components/CSprite2DComponent.h"

class CTextureManager
{
private:
	std::unordered_map<std::string, CSprite2DComponent> mTextureData;		//���f���f�[�^�i�[����

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
	CSprite2DComponent& GetTexture(std::string filePath);
};
