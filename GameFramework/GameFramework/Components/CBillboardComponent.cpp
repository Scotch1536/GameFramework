//!
//! @file
//! @brief ビルボードコンポーネントのソースファイル
//!

#include "../Managers/CDirectXResourceManager.h"
#include "../Managers/CGameManager.h"

#include "CBillboardComponent.h"
#include "CRenderComponent.h"

CBillboardComponent::CBillboardComponent(CActor& owner , CTransform& parentTrans , std::string texturePath ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPlaneMeshComponent(owner , parentTrans , { 1.0f,1.0f,1.0f,1.0f } , vertexShaderPath , pixelShaderPath , false)
{
	Transform.SetIsBillboard(true);

	//初期化
	Init(vertexShaderPath , pixelShaderPath);

	mTextureSRV = CDirectXResourceManager::GetInstance().GetTextureSRV(texturePath);
}

void CBillboardComponent::Init(std::string vertexShaderPath , std::string pixelShaderPath)
{
	//頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	unsigned int numElements = ARRAYSIZE(layout);

	mRenderComponent.GenerateVertexShader(layout , numElements , vertexShaderPath);		//頂点シェーダ生成
	mRenderComponent.GeneratePixelShader(pixelShaderPath);								//ピクセルシェーダ生成

	CreateVertexData();		//頂点データ作成
	CreateIndexData();		//インデックスデータ作成

	//頂点&インデックスバッファの生成
	GenerateVertexAndIndexBuffer();
}

void CBillboardComponent::Update()
{
	//描画命令の追加
	mOwnerInterface.AddRenderOrder({ *this,ERenderOption::BILLBOARD,CGameManager::GetInstance().CalcDistanceToCamera(Transform.GetWorldLocation()) });
}

void CBillboardComponent::Render()
{
	//GPUへの行列のセットをリクエスト
	Transform.RequestSetMatrix();

	//描画
	mRenderComponent.Render(sizeof(SVertexUV) , mIndices.size() , mTextureSRV , mVertexBuffer.Get() , mIndexBuffer.Get() , nullptr);
}