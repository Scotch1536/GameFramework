#include "../Managers/CDirectXResourceManager.h"
#include "../Actor/CActor.h"

#include "CRenderComponent.h"
#include "CDisplay2DComponent.h"

CDisplay2DComponent::CDisplay2DComponent(CActor& owner , CTransform& parentTrans , std::string texturePath , const XMFLOAT4& color,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPlaneMeshComponent(owner , parentTrans , color , vertexShaderPath , pixelShaderPath , false)
{
	Init(vertexShaderPath , pixelShaderPath);

	mTextureSRV = CDirectXResourceManager::GetInstance().GetTextureSRV(texturePath);
}

CDisplay2DComponent::CDisplay2DComponent(CActor& owner , CTransform& parentTrans , std::string texturePath ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPlaneMeshComponent(owner , parentTrans , { 1.0f,1.0f,1.0f,1.0f } , vertexShaderPath , pixelShaderPath , false)
{
	Init(vertexShaderPath , pixelShaderPath);

	mTextureSRV = CDirectXResourceManager::GetInstance().GetTextureSRV(texturePath);
}

CDisplay2DComponent::CDisplay2DComponent(CActor& owner , CTransform& parentTrans , const XMFLOAT4& color ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPlaneMeshComponent(owner , parentTrans , color , vertexShaderPath , pixelShaderPath , false)
{
	Init(vertexShaderPath , pixelShaderPath);
}

void CDisplay2DComponent::Init(std::string vertexShaderPath , std::string pixelShaderPath)
{
	// 頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	unsigned int numElements = ARRAYSIZE(layout);

	mRenderComponent.GenerateVertexShader(layout , numElements , vertexShaderPath);
	mRenderComponent.GeneratePixelShader(pixelShaderPath);

	CreateVertexData();
	CreateIndexData();

	GenerateVertexAndIndexBuffer();
}

XMFLOAT2& CDisplay2DComponent::GetUV(int index)
{
	return mVertices.at(index).Tex;
};

void CDisplay2DComponent::Update()
{
	if(!this->mIsTranslucent)this->mOwnerInterface.AddRenderOrder({ *this,ERenderOption::OPACITY2D });
	else this->mOwnerInterface.AddRenderOrder({ *this,ERenderOption::TRANSLUCENT2D });

	//頂点セット
	D3D11_MAPPED_SUBRESOURCE pData;

	HRESULT hr = CDirectXGraphics::GetInstance()->GetImmediateContext()->Map(mVertexBuffer.Get() , 0 , D3D11_MAP_WRITE_DISCARD , 0 , &pData);
	if(SUCCEEDED(hr))
	{
		memcpy_s(pData.pData , pData.RowPitch , mVertices.data() , sizeof(SVertex2D) * mVertices.size());
		CDirectXGraphics::GetInstance()->GetImmediateContext()->Unmap(mVertexBuffer.Get() , 0);
	}
}

void CDisplay2DComponent::Render()
{
	this->Transform.RequestSetMatrix();

	this->mRenderComponent.Render(sizeof(SVertex2D) , this->mIndices.size() , mTextureSRV , this->mVertexBuffer.Get() , this->mIndexBuffer.Get() , nullptr);
}