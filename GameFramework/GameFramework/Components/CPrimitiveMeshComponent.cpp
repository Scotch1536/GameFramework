//!
//! @file
//! @brief プリミティブメッシュコンポーネントのソースファイル
//!

#include "../Actor/CActor.h"
#include "../ExternalCode/Shader.h"
#include "../ExternalCode/CDirectxGraphics.h"
#include "../Managers/CGameManager.h"

#include "CPrimitiveMeshComponent.h"
#include "CRenderComponent.h"

template<class VertexType>
CPrimitiveMeshComponent<VertexType>::CPrimitiveMeshComponent(CActor& owner , CTransform& parentTrans , const XMFLOAT4& color , std::string vertexShaderPath , std::string pixelShaderPath)
	:CComponent(owner , 100) ,
	mRenderComponent(*new CRenderComponent(owner)) ,
	mColor(color) ,
	Transform(owner , parentTrans)
{}

template<class VertexType>
void CPrimitiveMeshComponent<VertexType>::Init(std::string vertexShaderPath , std::string pixelShaderPath)
{
	//半透明チェック
	CheckTranslucent();

	// 頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	unsigned int numElements = ARRAYSIZE(layout);

	mRenderComponent.GenerateVertexShader(layout , numElements , vertexShaderPath);		//頂点シェーダ生成
	mRenderComponent.GeneratePixelShader(pixelShaderPath);								//ピクセルシェーダ生成

	CreateVertexData();		//頂点データ作成
	CreateIndexData();		//インデックスデータ作成

	//頂点&インデックスバッファ生成
	GenerateVertexAndIndexBuffer();
}

template<class VertexType>
void CPrimitiveMeshComponent<VertexType>::GenerateVertexAndIndexBuffer()
{
	ID3D11Device* buf = CDirectXGraphics::GetInstance()->GetDXDevice();

	// 頂点バッファ生成
	bool sts = CreateVertexBufferWrite(buf , static_cast<unsigned int>(sizeof(VertexType)) ,
		static_cast<unsigned int>(mVertices.size()) ,
		mVertices.data() , &mVertexBuffer);
	if(!sts)
	{
		MessageBox(NULL , "CreateBuffer(vertex buffer) error" , "Error" , MB_OK);
		exit(1);
	}

	// インデックスバッファ生成
	sts = CreateIndexBuffer(buf , mIndices.size() ,
		mIndices.data() , &mIndexBuffer);
	if(!sts)
	{
		MessageBox(NULL , "CreateBuffer(index buffer) error" , "Error" , MB_OK);
		exit(1);
	}
}

template<class VertexType>
void CPrimitiveMeshComponent<VertexType>::Update()
{
	//半透明じゃなければ
	if(!mIsTranslucent)mOwnerInterface.AddRenderOrder({ *this,ERenderOption::OPACITY3D });																				//描画命令追加
	else mOwnerInterface.AddRenderOrder({ *this,ERenderOption::TRANSLUCENT3D,CGameManager::GetInstance().CalcDistanceToCamera(Transform.GetWorldLocation()) });			//描画命令追加
}

template<class VertexType>
void CPrimitiveMeshComponent<VertexType>::Render()
{
	//GPUへの行列のセットをリクエスト
	Transform.RequestSetMatrix();

	//描画
	mRenderComponent.Render(sizeof(VertexType) , mIndices.size() , nullptr , mVertexBuffer.Get() , mIndexBuffer.Get() , nullptr);
}

template<class VertexType>
void CPrimitiveMeshComponent<VertexType>::SetColor(const XMFLOAT4& color)
{
	mColor = color;

	//半透明チェック
	CheckTranslucent();
}

void CPrimitiveMeshComponent<SVertexColor>::SetColor(const XMFLOAT4& color)
{
	mColor = color;

	//半透明チェック
	CheckTranslucent();

	for(auto& vertex : mVertices)
	{
		vertex.Color = color;
	}

	//頂点バッファ更新
	UpdateVertexBuffer();
}

void CPrimitiveMeshComponent<SVertex2D>::SetColor(const XMFLOAT4& color)
{
	mColor = color;

	//半透明チェック
	CheckTranslucent();

	for(auto& vertex : mVertices)
	{
		vertex.Color = color;
	}

	//頂点バッファ更新
	UpdateVertexBuffer();
}

template<class VertexType>
void CPrimitiveMeshComponent<VertexType>::UpdateVertexBuffer()
{
	D3D11_MAPPED_SUBRESOURCE pData;

	//頂点バッファ更新
	HRESULT hr = CDirectXGraphics::GetInstance()->GetImmediateContext()->Map(mVertexBuffer.Get() , 0 , D3D11_MAP_WRITE_DISCARD , 0 , &pData);
	if(SUCCEEDED(hr))
	{
		memcpy_s(pData.pData , pData.RowPitch , mVertices.data() , sizeof(VertexType) * mVertices.size());
		CDirectXGraphics::GetInstance()->GetImmediateContext()->Unmap(mVertexBuffer.Get() , 0);
	}
}

template class CPrimitiveMeshComponent<SVertexColor>;
template class CPrimitiveMeshComponent<SVertexUV>;
template class CPrimitiveMeshComponent<SVertex2D>;