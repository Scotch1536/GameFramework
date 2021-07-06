#include "../Actor/CActor.h"
#include "../ExternalCode/dx11mathutil.h"
#include "../ExternalCode/Shader.h"
#include "../ExternalCode/CDirectxGraphics.h"

#include "CSphereMeshComponent.h"
#include "CRenderComponent.h"

CSphereMeshComponent::CSphereMeshComponent(CActor& owner , float radius , int divNum , XMFLOAT4 color)
	:CComponent(owner , 100) ,
	mRenderComponent(*new CRenderComponent(owner)) ,
	mColor(color) ,
	mRadius(radius) ,
	mDivisionNumber(divNum) ,
	Transform(owner)
{
	if(mColor.w < 1.0f)
	{
		isAlpha = true;
	}
	else
	{
		//アクター(owner)にレンダー担当のコンポーネントとして登録
		mOwnerInterface.AddRenderComponent(*this);
	}

	CreateVertex();
	CreateIndex();

	ID3D11Device* buf = CDirectXGraphics::GetInstance()->GetDXDevice();

	// 頂点バッファ生成
	bool sts = CreateVertexBufferWrite(buf , static_cast<unsigned int>(sizeof(SVertexUV)) ,
		static_cast<unsigned int>(mVertex.size()) ,
		mVertex.data() , &mVertexBuffer);
	if(!sts)
	{
		MessageBox(NULL , "CreateBuffer(vertex buffer) error" , "Error" , MB_OK);
	}

	// インデックスバッファ生成
	sts = CreateIndexBuffer(buf , static_cast<unsigned int>(mFace.size() * 3) ,
		mFace.data() , &mIndexBuffer);
	if(!sts)
	{
		MessageBox(NULL , "CreateBuffer(index buffer) error" , "Error" , MB_OK);
	}

	// 頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	unsigned int numElements = ARRAYSIZE(layout);

	mRenderComponent.GenerateVertexShader(layout , numElements , "Shader/vsnotex.hlsl");
	mRenderComponent.GeneratePixelShader("Shader/psnotex.hlsl");
}

void CSphereMeshComponent::CreateVertex()
{
	float azimuth = 0.0f;			// 方位角
	float elevation = 0.0f;			// 仰角

	XMFLOAT3 Normal;

	// 方位角と仰角から球メッシュの頂点データを作成
	for(unsigned int y = 0; y <= mDivisionNumber; y++)
	{
		elevation = (XM_PI* static_cast<float>(y)) / static_cast<float>(mDivisionNumber);		// 仰角をセット

		float r = mRadius * sinf(elevation);					// 仰角に応じた半径を計算

		for(unsigned int x = 0; x <= mDivisionNumber; x++)
		{
			azimuth = (2 * XM_PI * static_cast<float>(x)) / static_cast<float>(mDivisionNumber);		// 方位角をセット

			SVertexColor v;
			v.Pos.x = r * cosf(azimuth);
			v.Pos.y = mRadius * cosf(elevation);
			v.Pos.z = r * sinf(azimuth);

			DX11Vec3Normalize(Normal , Normal);			// 法線を計算
			v.Normal = Normal;							// 法線をセット

			v.Color = mColor;				// 頂点カラー

			mVertex.emplace_back(v);
		}
	}
}

void CSphereMeshComponent::CreateIndex()
{
	// インデックス生成
	for(unsigned int y = 0; y < mDivisionNumber; y++)
	{
		for(unsigned int x = 0; x < mDivisionNumber; x++)
		{
			int count = (mDivisionNumber + 1)*y + x;			// 左上座標のインデックス

			Face f;
			// 上半分
			f.idx[0] = count;
			f.idx[1] = count + 1;
			f.idx[2] = count + 1 + (mDivisionNumber + 1);

			mFace.emplace_back(f);

			// 下半分
			f.idx[0] = count;
			f.idx[1] = count + (mDivisionNumber + 1) + 1;
			f.idx[2] = count + (mDivisionNumber + 1);

			mFace.emplace_back(f);
		}
	}
}

void CSphereMeshComponent::Update()
{
	if(isAlpha)mOwnerInterface.RequestAddAlphaRenderComponentToLevel(*this);
}

void CSphereMeshComponent::Render()
{
	Transform.RequestSetMatrix();

	mRenderComponent.Render(sizeof(SVertexColor) , static_cast<unsigned int>(mFace.size() * 3) , nullptr , mVertexBuffer.Get() , mIndexBuffer.Get() , nullptr);
}