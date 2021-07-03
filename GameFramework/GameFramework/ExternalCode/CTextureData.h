#pragma once
#include <string>

#include "../ExternalCode/dx11mathutil.h"
#include "../ExternalCode/VertexProto.h"

class CTextureData
{
private:
	//ComPtr<ID3D11Buffer> mVertexBuffer = nullptr; // ���_�o�b�t�@
	//ComPtr<ID3D11Buffer> mIndexBuffer = nullptr; // �C���f�b�N�X�o�b�t�@
	//Vertex mVertex[4]; // ��`�S���_
	ID3D11ShaderResourceView* mSRV = nullptr;
	ID3D11Resource*	mResource = nullptr;
public:
	CTextureData() = default;
	~CTextureData();
	bool Load(std::string filePath);

};