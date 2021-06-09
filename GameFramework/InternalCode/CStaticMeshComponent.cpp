#include <string>

#include "CStaticMeshComponent.h"
#include "CChildTransform.h"
#include "CRenderComponent.h"
#include "CModelDataManager.h"
#include "CActor.h"

CStaticMeshComponent::CStaticMeshComponent(IActor& owner , ModelData& model , int priority)
	:CComponent(owner , priority) ,
	mTransform(owner.GetTransform()) ,
	mModel(&model) ,
	mRenderComponent(*new CRenderComponent(owner))
{
	mAttribute = CComponent::EAttribute::RENDER;

	//アクター(owner)にレンダー担当のコンポーネントとして登録
	owner.RegisterRenderComponent(*this);

	// 頂点データの定義（アニメーション対応）
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	unsigned int numElements = ARRAYSIZE(layout);

	mRenderComponent.GenerateVertexShader(layout , numElements , "Shader/vs.hlsl");
	mRenderComponent.GeneratePixelShader("Shader/ps.hlsl");
}

void CStaticMeshComponent::Render()
{
	mTransform.RequestSetMatrix();

	for(auto& mesh : mModel->GetMeshes())
	{
		unsigned int indexSize = static_cast <unsigned int>(mesh.m_indices.size());

		if(mesh.m_textures.size() >= 1)
		{
			mRenderComponent.Render(indexSize , mesh.m_textures[0].texture ,
				mesh.GetVertexBuffer() , mesh.GetIndexBuffer() , mesh.GetConstantBuffer());
		}
		else
		{
			MessageBox(NULL , "Not Found Texture!!" , "error" , MB_OK);
			exit(1);
			//TO DO
		}
	}
}