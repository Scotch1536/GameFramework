#include "../Managers/CDirectXResourceManager.h"
#include "../Actor/CActor.h"

#include "CRenderComponent.h"
#include "CDisplay2DComponent.h"

CDisplay2DComponent::CDisplay2DComponent(CActor& owner , CTransform& parentTrans , std::string texturePath ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPlaneMeshComponent(owner , parentTrans , { 1.0f,1.0f,1.0f,1.0f } , vertexShaderPath , pixelShaderPath , false)
{
	Init(vertexShaderPath , pixelShaderPath);

	mTextureSRV = CDirectXResourceManager::GetInstance().GetTextureSRV(texturePath);
}

void CDisplay2DComponent::Init(std::string vertexShaderPath , std::string pixelShaderPath)
{
	// 頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	unsigned int numElements = ARRAYSIZE(layout);

	mRenderComponent.GenerateVertexShader(layout , numElements , vertexShaderPath);
	mRenderComponent.GeneratePixelShader(pixelShaderPath);

	CreateVertexData();
	CreateIndexData();

	GenerateVertexAndIndexBuffer();
}

void CDisplay2DComponent::Update()
{
	mOwnerInterface.RequestAdd2DRenderComponentToLevel(*this);
}

void CDisplay2DComponent::Render()
{
	Transform.RequestSetMatrix();

	mRenderComponent.Render(sizeof(SVertex2D) , mIndices.size() , mTextureSRV , mVertexBuffer.Get() , mIndexBuffer.Get() , nullptr);
}