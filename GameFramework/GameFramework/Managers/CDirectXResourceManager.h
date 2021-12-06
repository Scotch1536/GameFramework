#pragma once
#include <unordered_map>

#include "../ExternalCode/CDirectxGraphics.h"

class CDirectXResourceManager
{
private:
	std::unordered_map<std::string , ComPtr<ID3D11Resource>> mTextureResourceMap;
	std::unordered_map<std::string , ComPtr<ID3D11ShaderResourceView>> mTextureSRVMap;
	std::unordered_map<std::string , ComPtr<ID3D11VertexShader>> mVertexShaderMap;
	std::unordered_map<std::string , ComPtr<ID3D11PixelShader>> mPixelShaderMap;
	std::unordered_map<std::string , ComPtr<ID3D11InputLayout>> mVertexLayoutMap;

	CDirectXResourceManager();

	//コピー＆ムーブ禁止
	CDirectXResourceManager(const CDirectXResourceManager&) = delete;
	CDirectXResourceManager& operator=(const CDirectXResourceManager&) = delete;
	CDirectXResourceManager(CDirectXResourceManager&&) = delete;
	CDirectXResourceManager& operator=(CDirectXResourceManager&&) = delete;

public:
	static CDirectXResourceManager& GetInstance();

	ID3D11ShaderResourceView* GetTextureSRV(std::string filePath);

	ID3D11VertexShader* GetVertexShader(std::string filePath);

	ID3D11PixelShader* GetPixelShader(std::string filePath);

	ID3D11InputLayout* GetVertexLayout(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , std::string vsFilePath);
};