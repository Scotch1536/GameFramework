#include "CRenderComponent.h"

#include "CBillboardComponent.h"

CBillboardComponent::CBillboardComponent(CActor& owner , CTransform& parentTrans ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPlaneMeshComponent<SVertexUV>(owner , parentTrans , { 1.0f,1.0f,1.0f,1.0f } , vertexShaderPath , pixelShaderPath , false)
{
	Init(vertexShaderPath , pixelShaderPath);
}

void CBillboardComponent::Init(std::string vertexShaderPath , std::string pixelShaderPath)
{
	mIsTranslucent = true;

	// 頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	unsigned int numElements = ARRAYSIZE(layout);

	mRenderComponent.GenerateVertexShader(layout , numElements , vertexShaderPath);
	mRenderComponent.GeneratePixelShader(pixelShaderPath);

	CreateVertexData();
	CreateIndexData();

	GenerateVertexAndIndexBuffer();
}