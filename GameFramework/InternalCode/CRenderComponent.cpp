#include "CRenderComponent.h"
#include "CDirectxGraphics.h"
#include "Shader.h"

CRenderComponent::CRenderComponent(IActor& owner):CComponent(owner)
{
	mPriority = 100;
}

bool CRenderComponent::GenerateVertexShader(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , const char* vsfile)
{
	ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();

	// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	bool sts = CreateVertexShader(device ,
		vsfile ,
		"main" ,
		"vs_5_0" ,
		layout ,
		layoutSize ,
		&mVertexShader ,
		&mVertexLayout);
	if(!sts)
	{
		MessageBox(nullptr , "CreateVertexShader error" , "error" , MB_OK);
		return false;
	}

	return true;
}

bool CRenderComponent::GeneratePixelShader(const char* psfile)
{
	ID3D11Device* device = CDirectXGraphics::GetInstance()->GetDXDevice();

	// ピクセルシェーダーを生成
	bool sts = CreatePixelShader(
		device ,
		psfile ,
		"main" ,
		"ps_5_0" ,
		&mPixelShader);
	if(!sts)
	{
		MessageBox(nullptr , "CreatePixelShader error" , "error" , MB_OK);
		return false;
	}

	return true;
}

void CRenderComponent::SetData(unsigned int indexSize ,
	ID3D11ShaderResourceView* shaderResourceView ,
	ID3D11Buffer* vertexBuffer ,
	ID3D11Buffer* indexBuffer ,
	ID3D11Buffer* cBMaterial)
{
	mIndexBuffer = indexBuffer;
	mShaderResourceView = shaderResourceView;
	mVertexBuffer = vertexBuffer;
	mIndexBuffer = indexBuffer;
	mCBMaterial = cBMaterial;
}

void CRenderComponent::Render()
{
	ID3D11DeviceContext*	devcontext;			// デバイスコンテキスト

	unsigned int stride = sizeof(Vertex);
	unsigned int offset = 0;

	devcontext = CDirectXGraphics::GetInstance()->GetImmediateContext();
	// 頂点フォーマットをセット
	devcontext->IASetInputLayout(mVertexLayout.Get());
	// 頂点シェーダーをセット
	devcontext->VSSetShader(mVertexShader.Get() , nullptr , 0);
	// ピクセルシェーダーをセット
	devcontext->PSSetShader(mPixelShader.Get() , nullptr , 0);
	// 頂点バッファをセット
	devcontext->IASetVertexBuffers(0 , 1 , &mVertexBuffer , &stride , &offset);
	// インデックスバッファをセット
	devcontext->IASetIndexBuffer(mIndexBuffer , DXGI_FORMAT_R32_UINT , 0);
	// トポロジーをセット
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// SRVをセット
	devcontext->PSSetShaderResources(0 , 1 , &mShaderResourceView);

	//else {
	//	// 真っ白SRVをセット
	//	devcontext->PSSetShaderResources(0, 1, &m_whitesrv);
	//}

	// マテリアルをVSへセット
	devcontext->VSSetConstantBuffers(3 , 1 , &mCBMaterial);
	devcontext->PSSetConstantBuffers(3 , 1 , &mCBMaterial);

	// インデックスバッファを利用して描画
	devcontext->DrawIndexed(mIndexSize , 0 , 0);
}

void CRenderComponent::Update()
{

}