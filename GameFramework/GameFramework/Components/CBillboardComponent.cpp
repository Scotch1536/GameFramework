#include "../Managers/CDirectXResourceManager.h"
#include "../Managers/CGameManager.h"

#include "CBillboardComponent.h"
#include "CRenderComponent.h"

CBillboardComponent::CBillboardComponent(CActor& owner , CTransform& parentTrans , std::string texturePath ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPlaneMeshComponent(owner , parentTrans , { 1.0f,1.0f,1.0f,1.0f } , vertexShaderPath , pixelShaderPath , false)
{
	Transform.SetIsBillboard(true);

	Init(vertexShaderPath , pixelShaderPath);

	mTextureSRV = CDirectXResourceManager::GetInstance().GetTextureSRV(texturePath);
}

void CBillboardComponent::Init(std::string vertexShaderPath , std::string pixelShaderPath)
{
	// ���_�f�[�^�̒�`
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

void CBillboardComponent::Update()
{
	mOwnerInterface.AddRenderOrder({ *this,ERenderOption::BILLBOARD,CGameManager::GetInstance().CalcDistanceToCamera(Transform.GetWorldLocation()) });

	//���_�Z�b�g
	D3D11_MAPPED_SUBRESOURCE pData;

	HRESULT hr = CDirectXGraphics::GetInstance()->GetImmediateContext()->Map(mVertexBuffer.Get() , 0 , D3D11_MAP_WRITE_DISCARD , 0 , &pData);
	if(SUCCEEDED(hr))
	{
		memcpy_s(pData.pData , pData.RowPitch , mVertices.data() , sizeof(SVertex2D) * mVertices.size());
		CDirectXGraphics::GetInstance()->GetImmediateContext()->Unmap(mVertexBuffer.Get() , 0);
	}
}

void CBillboardComponent::Render()
{
	Transform.RequestSetMatrix();

	mRenderComponent.Render(sizeof(SVertexUV) , mIndices.size() , mTextureSRV , mVertexBuffer.Get() , mIndexBuffer.Get() , nullptr);
}