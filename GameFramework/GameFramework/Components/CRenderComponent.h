#pragma once
#include <d3d11.h>
#include <wrl/client.h>

#include "../Data/VertexProto.h"

#include "CComponent.h"

using Microsoft::WRL::ComPtr;

//レンダーコンポーネントクラス
class CRenderComponent :public CComponent
{
private:
	ID3D11VertexShader* mVertexShader = nullptr;		// 頂点シェーダー
	ID3D11PixelShader* mPixelShader = nullptr;			// ピクセルシェーダー
	ID3D11InputLayout* mVertexLayout = nullptr;			// 頂点フォーマット

public:
	CRenderComponent(CActor& owner , int priority = 100);

	//頂点シェーダ生成
	void GenerateVertexShader(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , std::string vsFilePath);

	//ピクセルシェーダ生成
	void GeneratePixelShader(std::string psFilePath);

	//描画
	void Render(unsigned int stride,
		unsigned int indexSize ,
		ID3D11ShaderResourceView* shaderResourceView ,
		ID3D11Buffer* vertexBuffer ,
		ID3D11Buffer* indexBuffer ,
		ID3D11Buffer* cBMaterial);

};