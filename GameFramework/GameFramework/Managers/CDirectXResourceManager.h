#pragma once
#include <unordered_map>

#include "../ExternalCode/CDirectxGraphics.h"

class CDirectXResourceManager
{
private:
	std::unordered_map<std::string , ComPtr<ID3D11Resource>> mTextureResource;
	std::unordered_map<std::string , ComPtr<ID3D11ShaderResourceView>> mTextureSRV;

	CDirectXResourceManager() = default;

	//コピー＆ムーブ禁止
	CDirectXResourceManager(const CDirectXResourceManager&) = delete;
	CDirectXResourceManager& operator=(const CDirectXResourceManager&) = delete;
	CDirectXResourceManager(CDirectXResourceManager&&) = delete;
	CDirectXResourceManager& operator=(CDirectXResourceManager&&) = delete;

public:
	static CDirectXResourceManager& GetInstance();

	ID3D11ShaderResourceView* GetTextureSRV(std::string filePath);
};