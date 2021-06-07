#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include "CComponent.h"
#include "VertexProto.h"

using Microsoft::WRL::ComPtr;

//レンダーコンポーネントクラス
class CRenderComponent :public CComponent
{
protected:
	//unsigned int mIndexSize = 0;		//インデックスサイズ

	ComPtr<ID3D11VertexShader> mVertexShader;			// 頂点シェーダー
	ComPtr<ID3D11PixelShader> mPixelShader;				// ピクセルシェーダー
	ComPtr<ID3D11InputLayout> mVertexLayout;			// 頂点フォーマット

	//ComPtr<ID3D11Resource> mTexRes;								// テクスチャリソース
	//ID3D11ShaderResourceView* mShaderResourceView = nullptr;		// SRV

	//ID3D11Buffer* mVertexBuffer = nullptr;			// 頂点バッファ
	//ID3D11Buffer* mIndexBuffer = nullptr;			// インデックスバッファ
	//ID3D11Buffer* mCBMaterial = nullptr;			// マテリアル用コンスタントバッファ

public:
	CRenderComponent(IActor& owner);

	//頂点シェーダ生成
	bool GenerateVertexShader(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , const char* vsfile);

	//ピクセルシェーダ生成
	bool GeneratePixelShader(const char* psfile);

	////データのセット（初期化）
	//void SetData(unsigned int indexSize ,
	//	ID3D11ShaderResourceView* shaderResourceView ,
	//	ID3D11Buffer* vertexBuffer ,
	//	ID3D11Buffer* indexBuffer ,
	//	ID3D11Buffer* cBMaterial);

	//描画
	void Render(unsigned int indexSize ,
		ID3D11ShaderResourceView* shaderResourceView ,
		ID3D11Buffer* vertexBuffer ,
		ID3D11Buffer* indexBuffer ,
		ID3D11Buffer* cBMaterial);

	//更新
	void Update()override;
};