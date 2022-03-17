//!
//! @file
//! @brief ディスプレイ2Dコンポーネントのソースファイル
//!

#include "../Managers/CDirectXResourceManager.h"
#include "../Actor/CActor.h"

#include "CRenderComponent.h"
#include "CDisplay2DComponent.h"

CDisplay2DComponent::CDisplay2DComponent(CActor& owner , CTransform& parentTrans , std::string texturePath , const XMFLOAT4& color ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPlaneMeshComponent(owner , parentTrans , color , vertexShaderPath , pixelShaderPath , false)
{
	mTextureSRV = CDirectXResourceManager::GetInstance().GetTextureSRV(texturePath);

	//初期化
	Init(vertexShaderPath , pixelShaderPath);
}

CDisplay2DComponent::CDisplay2DComponent(CActor& owner , CTransform& parentTrans , const XMFLOAT4& color ,
	std::string vertexShaderPath , std::string pixelShaderPath)
	:CPlaneMeshComponent(owner , parentTrans , color , vertexShaderPath , pixelShaderPath , false)
{
	//初期化
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

	mRenderComponent.GenerateVertexShader(layout , numElements , vertexShaderPath);		//頂点シェーダ生成
	mRenderComponent.GeneratePixelShader(pixelShaderPath);								//ピクセルシェーダ生成

	CreateVertexData();		//頂点データ作成
	CreateIndexData();		//インデックスデータ作成

	//頂点&インデックスバッファの生成
	GenerateVertexAndIndexBuffer();
}

XMFLOAT2* CDisplay2DComponent::GetUV(int index)
{
	return &mVertices.at(index).Tex;
};

void CDisplay2DComponent::Update()
{
	//半透明じゃなければ
	if(!this->mIsTranslucent)this->mOwnerInterface.AddRenderOrder({ *this,ERenderOption::OPAQUE2D });		//描画命令追加
	else this->mOwnerInterface.AddRenderOrder({ *this,ERenderOption::TRANSLUCENT2D });						//描画命令追加
}

void CDisplay2DComponent::Render()
{
	//GPUへの行列のセットをリクエスト
	this->Transform.RequestSetMatrix();

	//描画
	this->mRenderComponent.Render(sizeof(SVertex2D) , this->mIndices.size() , mTextureSRV , this->mVertexBuffer.Get() , this->mIndexBuffer.Get() , nullptr);
}