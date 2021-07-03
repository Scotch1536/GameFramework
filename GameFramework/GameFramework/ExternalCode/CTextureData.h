#pragma once
#include <string>

#include "../ExternalCode/dx11mathutil.h"
#include "../ExternalCode/VertexProto.h"

class CTextureData
{
private:
	ComPtr<ID3D11Buffer> mVertexBuffer = nullptr; // 頂点バッファ
	ComPtr<ID3D11Buffer> mIndexBuffer = nullptr; // インデックスバッファ
	Vertex mVertex[4]; // 矩形４頂点
	ID3D11ShaderResourceView* mSRV = nullptr;
	ID3D11Resource*	mResource = nullptr;
public:
	CTextureData() = default;
	~CTextureData();
	bool Load(std::string filePath);

};