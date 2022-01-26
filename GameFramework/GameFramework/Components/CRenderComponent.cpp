#include <filesystem>

#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/Shader.h"
#include "../Managers/CDirectXResourceManager.h"

#include "CRenderComponent.h"

//!
//! @file
//! @brief レンダーコンポーネントのソースファイル
//!

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
	ID3D11Buffer* materialCB)
{
	unsigned int offset = 0;

	ID3D11DeviceContext* devcontext = CDirectXGraphics::GetInstance()->GetImmediateContext();

	//頂点フォーマットをセット
	devcontext->IASetInputLayout(mVertexLayout);

	//頂点シェーダーをセット
	devcontext->VSSetShader(mVertexShader , nullptr , 0);

	//ピクセルシェーダーをセット
	devcontext->PSSetShader(mPixelShader , nullptr , 0);

	//頂点バッファをセット
	devcontext->IASetVertexBuffers(0 , 1 , &vertexBuffer , &stride , &offset);

	//インデックスバッファをセット
	devcontext->IASetIndexBuffer(indexBuffer , DXGI_FORMAT_R32_UINT , 0);

	//トポロジーをセット
	devcontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//SRVが存在していれば
	if(shaderResourceView != nullptr)
	{
		//SRVをセット
		devcontext->PSSetShaderResources(0 , 1 , &shaderResourceView);
	}
	else
	{
		ID3D11ShaderResourceView* white = nullptr;

		//引数のパスがカレントディレクトリから存在するか
		if(std::filesystem::exists("Assets/Textures/White/white.bmp"))
		{
			white = CDirectXResourceManager::GetInstance().GetTextureSRV("Assets/Textures/White/white.bmp");
		}
		else if(std::filesystem::exists("GameFramework/Assets/white.bmp"))
		{
			white = CDirectXResourceManager::GetInstance().GetTextureSRV("GameFramework/Assets/white.bmp");
		}
		else
		{
			MessageBox(nullptr , "Not Found White Texture" , "error" , MB_OK);
		}

		//SRVをセット
		devcontext->PSSetShaderResources(0 , 1 , &white);
	}

	if(materialCB != nullptr)
	{
		//マテリアル定数バッファをセット
		devcontext->VSSetConstantBuffers(3 , 1 , &materialCB);
		devcontext->PSSetConstantBuffers(3 , 1 , &materialCB);
	}

	//インデックスバッファを利用して描画
	devcontext->DrawIndexed(indexSize , 0 , 0);
}