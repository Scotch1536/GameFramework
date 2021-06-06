#include <string>

#include "CStaticMeshComponent.h"
#include "CModelDataManager.h"

CStaticMeshComponent::CStaticMeshComponent(IActor& owner)
	:CComponent(owner) ,
	mRenderComponent(CRenderComponent(owner))
{
	mPriority = 90;

	// 頂点データの定義（アニメーション対応）
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	unsigned int numElements = ARRAYSIZE(layout);

	mRenderComponent.GenerateVertexShader(layout , numElements , "");
	mRenderComponent.GeneratePixelShader("");
}

void CStaticMeshComponent::SetModel(std::string filename , std::string resourcefolder)
{
	mModel = CModelManager::GetInstance().GetModel(filename , resourcefolder);
}

void CStaticMeshComponent::Update()
{

}

void CStaticMeshComponent::Render()
{
	for(auto& mesh : mModel.GetMeshes())
	{
		unsigned int indexSize = static_cast <unsigned int>(sizeof(mesh.m_indices));

		mRenderComponent.SetData(indexSize , mesh.m_textures[0].texture ,
			mesh.GetVertexBuffer() , mesh.GetIndexBuffer() , mesh.GetConstantBuffer());
	}
}