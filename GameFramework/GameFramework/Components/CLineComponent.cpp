#include <string>

#include "../ExternalCode/CDirectxGraphics.h"
#include "../Actor/CActor.h"
#include "CLineComponent.h"
#include "../Managers/CDirectXResourceManager.h"
#include "../ExternalCode/dx11mathutil.h"
#include"../Library/LCMath.h"

CLineComponent::CLineComponent(CActor& owner, XMFLOAT3 vertex1, XMFLOAT3 vertex2, XMFLOAT4 color, CTransform* parentTrans,
	std::string vertexShaderPath , 
	std::string pixelShaderPath, int priority) :CComponent(owner, priority), mOwnerTransform(parentTrans),mColor(color)
{
	mVertices.resize(2);
	mVertices.at(0) = vertex1;
	mVertices.at(1) = vertex2;
	mVertexSize = mVertices.size();

	Init(vertexShaderPath, pixelShaderPath);
}

void CLineComponent::Init(std::string vertexShaderPath, std::string pixelShaderPath)
{
	//アクター(owner)にレンダー担当のコンポーネントとして登録
	mOwnerInterface.AddRenderComponent(*this);

	// 頂点データの定義
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	unsigned int numElements = ARRAYSIZE(layout);

	CDirectXResourceManager& buf = CDirectXResourceManager::GetInstance();

	mVertexShader = buf.GetVertexShader(vertexShaderPath);
	mPixelShader = buf.GetPixelShader(pixelShaderPath);
	CreateVertexBufferWrite(CDirectXGraphics::GetInstance()->GetDXDevice(),
		sizeof(XMFLOAT3), mVertices.size(), (void*)mVertices.data(), &mVertexBuffer);

	if (mOwnerTransform != nullptr)
	{
		mOwnerTransform->SetMatrixUpdateTimeFunction(std::bind(&CLineComponent::SetShouldUpdate, std::ref(*this), true));
	}
}

//void CLineComponent::SetVertex(std::vector<XMFLOAT3>& v)
//{
//
//	D3D11_MAPPED_SUBRESOURCE pData;
//
//	HRESULT hr = CDirectXGraphics::GetInstance()->GetImmediateContext()->Map(mVertexBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData);
//	if (SUCCEEDED(hr)) {
//		memcpy_s(pData.pData, pData.RowPitch, (void*)(v.data()), sizeof(XMFLOAT3) * v.size());
//		CDirectXGraphics::GetInstance()->GetImmediateContext()->Unmap(mVertexBuffer.Get(), 0);
//	}
//
//	mVertexSize = v.size();
//}

void CLineComponent::Render()
{
	mOwnerTransform->RequestSetMatrix();
	ID3D11DeviceContext* devcontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	// 頂点バッファをセットする
	unsigned int stride = sizeof(XMFLOAT3);
	unsigned  offset = 0;
	devcontext->IASetVertexBuffers(0, 1, mVertexBuffer.GetAddressOf(), &stride, &offset);

	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);		// トポロジーをセット（旧プリミティブタイプ）
	devcontext->IASetInputLayout(mLayout.Get());			// 頂点レイアウトセット

	devcontext->VSSetShader(mVertexShader.Get(), nullptr, 0);		// 頂点シェーダーをセット
	devcontext->PSSetShader(mPixelShader.Get(), nullptr, 0);		// ピクセルシェーダーをセット

	devcontext->Draw(
		mVertexSize,							// 頂点数
		0);									// 頂点バッファの最初から使う
}


void CLineComponent::Update()
{
	if (mOwnerTransform != nullptr)
	{
		if (mShouldUpdate)
		{
			mShouldUpdate = false;
			XMFLOAT3 scale = mOwnerTransform->GetWorldScale();
			XMFLOAT4X4 resultMTX = mOwnerTransform->GetWorldMatrixResult();
			XMFLOAT4X4 scaleMTX;
			DX11MtxScale(scale.x, scale.y, scale.z, scaleMTX);
			LCMath::InverseMatrix(scaleMTX, scaleMTX);
			

		}
	}
}
