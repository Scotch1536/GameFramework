#include "../Managers/CDirectXResourceManager.h"
#include "../Actor/CActor.h"

#include "CRenderComponent.h"
#include "CDisplay2DComponent.h"

template<class VertexType>
CDisplay2DComponent<VertexType>::CDisplay2DComponent(CActor& owner , CTransform& parentTrans , std::string texturePath ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPlaneMeshComponent<VertexType>(owner , parentTrans , { 1.0f,1.0f,1.0f,1.0f } , vertexShaderPath , pixelShaderPath , false)
{
	Init(vertexShaderPath , pixelShaderPath);

	mTextureSRV = CDirectXResourceManager::GetInstance().GetTextureSRV(texturePath);
}

template<class VertexType>
CDisplay2DComponent<VertexType>::CDisplay2DComponent(CActor& owner , CTransform& parentTrans , XMFLOAT4 color ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPlaneMeshComponent<VertexType>(owner , parentTrans , color , vertexShaderPath , pixelShaderPath , false)
{
	Init(vertexShaderPath , pixelShaderPath);
}

void CDisplay2DComponent<SVertex2DUV>::Init(std::string vertexShaderPath , std::string pixelShaderPath)
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

void CDisplay2DComponent<SVertex2DColor>::Init(std::string vertexShaderPath , std::string pixelShaderPath)
{
	// 頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	unsigned int numElements = ARRAYSIZE(layout);

	mRenderComponent.GenerateVertexShader(layout , numElements , vertexShaderPath);
	mRenderComponent.GeneratePixelShader(pixelShaderPath);

	CreateVertexData();
	CreateIndexData();

	GenerateVertexAndIndexBuffer();
}

template<class VertexType>
void CDisplay2DComponent<VertexType>::Update()
{
	if(!this->mIsTranslucent)this->mOwnerInterface.AddRenderOrder({ *this,ERenderOption::OPACITY2D });
	else this->mOwnerInterface.AddRenderOrder({ *this,ERenderOption::TRANSLUCENT2D });
}

template<class VertexType>
void CDisplay2DComponent<VertexType>::Render()
{
	this->Transform.RequestSetMatrix();

	this->mRenderComponent.Render(sizeof(VertexType) , this->mIndices.size() , mTextureSRV , this->mVertexBuffer.Get() , this->mIndexBuffer.Get() , nullptr);
}

template class CDisplay2DComponent<SVertex2DUV>;
template class CDisplay2DComponent<SVertex2DColor>;