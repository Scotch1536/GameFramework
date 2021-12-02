#include <string>

#include "../Managers/CModelDataManager.h"
#include "../Managers/CDirectXResourceManager.h"
#include "../Actor/CActor.h"

#include "CStaticMeshComponent.h"
#include "CRenderComponent.h"

CStaticMeshComponent::CStaticMeshComponent(CActor& owner , CTransform& parentTrans , CModelData& model , std::string vertexShaderPath , std::string pixelShaderPath , int priority)
	:CComponent(owner , priority) ,
	Transform(owner , parentTrans) ,
	mModel(&model) ,
	mRenderComponent(*new CRenderComponent(owner))
{
	// 頂点データの定義（アニメーション対応）
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	unsigned int numElements = ARRAYSIZE(layout);

	mRenderComponent.GenerateVertexShader(layout , numElements , vertexShaderPath);
	mRenderComponent.GeneratePixelShader(pixelShaderPath);
}

void CStaticMeshComponent::Update()
{
	mOwnerInterface.AddRenderOrder({ *this,ERenderOption::OPACITY3D });
}

void CStaticMeshComponent::Render()
{
	Transform.RequestSetMatrix();

	for(auto& mesh : mModel.GetMeshes())
	{
		unsigned int indexSize = static_cast <unsigned int>(mesh.Indices.size());

		if(mesh.Textures.size() >= 1)
		{
			mRenderComponent.Render(sizeof(SVertexUV) , indexSize , mesh.Textures[0].Texture ,
				mesh.GetVertexBuffer() , mesh.GetIndexBuffer() , mesh.GetConstantBuffer());
		}
		else
		{
			mRenderComponent.Render(sizeof(SVertexUV) , indexSize , CDirectXResourceManager::GetInstance().GetTextureSRV("Assets/Textures/White/white.bmp") ,
				mesh.GetVertexBuffer() , mesh.GetIndexBuffer() , mesh.GetConstantBuffer());
		}
	}
}