#include <string>

#include "../Managers/CTextureManager.h"
#include "../Actor/CActor.h"

#include "CSprite2DComponent.h"
#include "CRenderComponent.h"

CSprite2DComponent::CSprite2DComponent(CActor& owner, CTextureData& texture, std::string vertexShaderPath, std::string pixelShaderPath, int priority)
	:CComponent(owner, priority), Transform(owner), 
	mTexture(texture), mRenderComponent(*new CRenderComponent(owner))
{
	//アクター(owner)にレンダー担当のコンポーネントとして登録
	mOwnerInterface.RegisterRenderComponent(*this);

	// 頂点データの定義（アニメーション対応）
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	//エレメント数確保
	unsigned int numElements = ARRAYSIZE(layout);
	mRenderComponent.GenerateVertexShader(layout, numElements, vertexShaderPath.c_str());
	mRenderComponent.GeneratePixelShader(pixelShaderPath.c_str());

	
}

void CSprite2DComponent::Render()
{
	Transform.RequestSetMatrix();

}