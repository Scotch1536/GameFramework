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

	ComPtr<ID3D11Buffer> mVertexBuffer = nullptr; // 頂点バッファ
	ComPtr<ID3D11Buffer> mIndexBuffer = nullptr; // インデックスバッファ
	Vertex mVertex[4]; // 矩形４頂点
public:
	CSprite2DComponent(CActor& owner, std::string fileName, int priority = 45);

	void Update()override;

	void Render()override;
};