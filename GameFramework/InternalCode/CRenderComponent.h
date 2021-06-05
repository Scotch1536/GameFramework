#pragma once

#include <d3d11.h>
#include <wrl/client.h>

#include "CComponent.h"
#include "VertexProto.h"

using Microsoft::WRL::ComPtr;

//インターフェース
class IRender
{
public:
	virtual ~IRender() {};
	virtual void Render() = 0;
};

class CRenderComponent :public CComponent,IRender
{
protected:

	unsigned int mIndexSize;
	ComPtr<ID3D11VertexShader> mVertexShader;			// 頂点シェーダー入れ物
	ComPtr<ID3D11PixelShader> mPixelShader;				// ピクセルシェーダー入れ物
	ComPtr<ID3D11InputLayout> mVertexLayout;			// 頂点フォーマット定義

	//ComPtr<ID3D11Resource> mTexRes;						// テクスチャリソース
	ComPtr<ID3D11ShaderResourceView> mTexture;			// SRV

	ComPtr<ID3D11Buffer>  mVertexBuffer;				// 頂点バッファ
	ComPtr<ID3D11Buffer>  mIndexBuffer;					// インデックスバッファ
	ComPtr<ID3D11Buffer>  mCBMaterial;					// マテリアル用コンスタントバッファ

public:
	void Render()override;
};