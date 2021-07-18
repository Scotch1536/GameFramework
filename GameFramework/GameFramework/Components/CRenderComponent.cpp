#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/Shader.h"
#include "../Managers/CDirectXResourceManager.h"

#include "CRenderComponent.h"

CRenderComponent::CRenderComponent(CActor& owner , int priority):CComponent(owner , priority)
{}

void CRenderComponent::GenerateVertexShader(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , std::string vsFilePath)
{
	CDirectXResourceManager& buf = CDirectXResourceManager::GetInstance();

	mVertexShader = buf.GetVertexShader(vsFilePath);
	mVertexLayout = buf.GetVertexLayout(layout , layoutSize , vsFilePath);
}

void CRenderComponent::GeneratePixelShader(std::string psFilePath)
{
	mPixelShader = CDirectXResourceManager::GetInstance().GetPixelShader(psFilePath);
}

void CRenderComponent::Render(unsigned int stride ,
	unsigned int indexSize ,
	ID3D11ShaderResourceView* shaderResourceView ,
	ID3D11Buffer* vertexBuffer ,
	ID3D11Buffer* indexBuffer ,
	ID3D11Buffer* cBMaterial)
{
	ID3D11DeviceContext*	devcontext;			// デバイスコンテキスト

	unsigned int offset = 0;

	devcontext = CDirectXGraphics::GetInstance()->GetImmediateContext();
	// 頂点フォーマットをセット
	devcontext->IASetInputLayout(mVertexLayout);
	// 頂点シェーダーをセット
	devcontext->VSSetShader(mVertexShader , nullptr , 0);
	// ピクセルシェーダーをセット
	devcontext->PSSetShader(mPixelShader , nullptr , 0);
	// 頂点バッファをセット
	devcontext->IASetVertexBuffers(0 , 1 , &vertexBuffer , &stride , &offset);
	// インデックスバッファをセット
	devcontext->IASetIndexBuffer(indexBuffer , DXGI_FORMAT_R32_UINT , 0);
	// トポロジーをセット
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// SRVをセット
	if(shaderResourceView != nullptr)
	{
		devcontext->PSSetShaderResources(0 , 1 , &shaderResourceView);
	}

	if(cBMaterial != nullptr)
	{
		// マテリアルをVSへセット
		devcontext->VSSetConstantBuffers(3 , 1 , &cBMaterial);
		devcontext->PSSetConstantBuffers(3 , 1 , &cBMaterial);
	}

	// インデックスバッファを利用して描画
	devcontext->DrawIndexed(indexSize , 0 , 0);
}