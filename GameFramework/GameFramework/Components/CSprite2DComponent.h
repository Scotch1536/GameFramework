#pragma once
#include <string>

#include "../ExternalCode/dx11mathutil.h"
#include "../ExternalCode/CDirectxGraphics.h"
#include "../Interfaces/IRender.h"
#include "../ExternalCode/VertexProto.h"

#include "CComponent.h"

class CRenderComponent;

class CSprite2DComponent :public CComponent,public IRender
{
private:

	ComPtr<ID3D11Buffer> mVertexBuffer = nullptr; // ���_�o�b�t�@
	ComPtr<ID3D11Buffer> mIndexBuffer = nullptr; // �C���f�b�N�X�o�b�t�@
	Vertex mVertex[4]; // ��`�S���_
public:
	CSprite2DComponent(CActor& owner, std::string fileName, int priority = 45);

	void Update()override;

	void Render()override;
};