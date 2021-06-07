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

//レンダーコンポーネントクラス
class CRenderComponent :public CComponent , IRender
{
protected:
	unsigned int mIndexSize = 0;		//インデックスサイズ

	ComPtr<ID3D11VertexShader> mVertexShader;			// 頂点シェーダー入れ物
	ComPtr<ID3D11PixelShader> mPixelShader;				// ピクセルシェーダー入れ物
	ComPtr<ID3D11InputLayout> mVertexLayout;			// 頂点フォーマット定義

	//ComPtr<ID3D11Resource> mTexRes;								// テクスチャリソース
	ID3D11ShaderResourceView* mShaderResourceView = nullptr;		// SRV

	ID3D11Buffer* mVertexBuffer = nullptr;			// 頂点バッファ
	ID3D11Buffer* mIndexBuffer = nullptr;			// インデックスバッファ
	ID3D11Buffer* mCBMaterial = nullptr;			// マテリアル用コンスタントバッファ

public:
	CRenderComponent(IActor& owner);

	bool GenerateVertexShader(D3D11_INPUT_ELEMENT_DESC* layout , unsigned int layoutSize , const char* vsfile);
	bool GeneratePixelShader(const char* psfile);

	//データのセット（初期化）
	void SetData(unsigned int indexSize ,
		ID3D11ShaderResourceView* shaderResourceView ,
		ID3D11Buffer* vertexBuffer ,
		ID3D11Buffer* indexBuffer ,
		ID3D11Buffer* cBMaterial);

	void Render()override;
	void Update()override;
};