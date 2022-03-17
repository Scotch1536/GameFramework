//!
//! @file
//! @brief スタティックメッシュコンポーネントのソースファイル
//!

#include <string>

#include "../Managers/CModelDataManager.h"
#include "../Managers/CDirectXResourceManager.h"
#include "../Actor/CActor.h"

#include "CStaticMeshComponent.h"
#include "CRenderComponent.h"

CStaticMeshComponent::CStaticMeshComponent(CActor& owner , CTransform& parentTrans , CModelData& model , std::string vertexShaderPath , std::string pixelShaderPath)
	:CComponent(owner , 90) ,
	Transform(owner , parentTrans) ,
	mModel(&model) ,
	mRenderComponent(*new CRenderComponent(owner))
{
	// 頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	unsigned int numElements = ARRAYSIZE(layout);

	mRenderComponent.GenerateVertexShader(layout , numElements , vertexShaderPath);		//頂点シェーダ生成
	mRenderComponent.GeneratePixelShader(pixelShaderPath);								//ピクセルシェーダ生成
}

void CStaticMeshComponent::Update()
{
	//描画命令追加
	mOwnerInterface.AddRenderOrder({ *this,ERenderOption::OPAQUE3D });
}

void CStaticMeshComponent::Render()
{
	//GPUへの行列のセットをリクエスト
	Transform.RequestSetMatrix();

	for(auto& mesh : mModel->GetMeshes())
	{
		unsigned int indexSize = static_cast <unsigned int>(mesh.Indices.size());

		//テクスチャがあるか
		if(mesh.Textures.size() >= 1)
		{
			//描画
			mRenderComponent.Render(sizeof(SVertexUV) , indexSize , mesh.Textures[0].TextureSRV ,
				mesh.GetVertexBuffer() , mesh.GetIndexBuffer() , mesh.GetConstantBuffer());
		}
		else
		{
			//描画
			mRenderComponent.Render(sizeof(SVertexUV) , indexSize , nullptr ,
				mesh.GetVertexBuffer() , mesh.GetIndexBuffer() , mesh.GetConstantBuffer());
		}
	}
}