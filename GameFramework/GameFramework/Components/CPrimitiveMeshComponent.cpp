#include "../Actor/CActor.h"
#include "../ExternalCode/Shader.h"
#include "../ExternalCode/CDirectxGraphics.h"

#include "CPrimitiveMeshComponent.h"
#include "CRenderComponent.h"

CPrimitiveMeshComponent::CPrimitiveMeshComponent(CActor& owner , CTransform& parentTrans , XMFLOAT4 color , std::string vertexShaderPath , std::string pixelShaderPath)
	:CComponent(owner , 100) ,
	mRenderComponent(*new CRenderComponent(owner)) ,
	mColor(color) ,
	Transform(parentTrans)
{
	if(mColor.w < 1.0f)
	{
		isTranslucent = true;
	}
	else
	{
		//アクター(owner)にレンダー担当のコンポーネントとして登録
		mOwnerInterface.AddRenderComponent(*this);
	}

	// 頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	unsigned int numElements = ARRAYSIZE(layout);

	mRenderComponent.GenerateVertexShader(layout , numElements , vertexShaderPath);
	mRenderComponent.GeneratePixelShader(pixelShaderPath);
}

void CPrimitiveMeshComponent::GenerateVertexAndIndexBuffer()
{
	ID3D11Device* buf = CDirectXGraphics::GetInstance()->GetDXDevice();

	// 頂点バッファ生成
	bool sts = CreateVertexBufferWrite(buf , static_cast<unsigned int>(sizeof(SVertexColor)) ,
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

void CPrimitiveMeshComponent::Update()
{
	if(isTranslucent)mOwnerInterface.RequestAddAlphaRenderComponentToLevel(*this);
}

void CPrimitiveMeshComponent::Render()
{
	Transform.RequestSetMatrix();

	mRenderComponent.Render(sizeof(SVertexColor) , mIndices.size() , nullptr , mVertexBuffer.Get() , mIndexBuffer.Get() , nullptr);
}