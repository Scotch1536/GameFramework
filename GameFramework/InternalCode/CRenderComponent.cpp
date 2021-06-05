#include "CRenderComponent.h"
#include "CDirectxGraphics.h"

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
	devcontext->IASetVertexBuffers(0 , 1 , mVertexBuffer.GetAddressOf() , &stride , &offset);
	// インデックスバッファをセット
	devcontext->IASetIndexBuffer(mIndexBuffer.Get() , DXGI_FORMAT_R32_UINT , 0);
	// トポロジーをセット
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// SRVをセット
	devcontext->PSSetShaderResources(0 , 1 , mTexture.GetAddressOf());

	//else {
	//	// 真っ白SRVをセット
	//	devcontext->PSSetShaderResources(0, 1, &m_whitesrv);
	//}

	// マテリアルをVSへセット
	devcontext->VSSetConstantBuffers(3 , 1 , mCBMaterial.GetAddressOf());
	devcontext->PSSetConstantBuffers(3 , 1 , mCBMaterial.GetAddressOf());

	// インデックスバッファを利用して描画
	devcontext->DrawIndexed(mIndexSize , 0 , 0);
}

void CRenderComponent::Update()
{

}